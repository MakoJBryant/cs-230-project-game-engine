//------------------------------------------------------------------------------
//
// File Name:	Sprite.c
// Author(s):	Mako J. Bryant (0068410)
// Project:		Project 2
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

// Essentials.
#include "stdafx.h"
#include "Sprite.h"
#include "DGL.h"
#include "Stream.h"
#include "Trace.h"
#include "Matrix2D.h"

// Components.
#include "SpriteSource.h"
#include "Transform.h"
#include "Mesh.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Sprite
{
	// The frame currently being displayed (for sprite sheets).
	unsigned int frameIndex;

	// The alpha transparency to use when drawing the sprite.
	float alpha;

	// The sprite source used when drawing (NULL = simple colored mesh).
	const SpriteSource* spriteSource;

	// The mesh used to draw the sprite.
	const Mesh* mesh;

	// Text string to render as sprite text.
	const char* text;

} Sprite;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new Sprite component.
Sprite* SpriteCreate(void)
{
	// Allocate memory for Sprite object.
	Sprite* newSprite = calloc(1, sizeof(Sprite));

	// Verify memory allocation succeeded.
	if (newSprite == NULL) {
		TraceMessage("Error: SpriteCreate failed to allocate memory.");
		return NULL;
	}

	// Set the default alpha value and return pointer to new Sprite.
	newSprite->alpha = 1.0f;
	return newSprite;
}

// Free the memory associated with a Sprite component.
void SpriteFree(Sprite** sprite)
{
	if (sprite == NULL || *sprite == NULL) {
		TraceMessage("Error: SpriteFree received NULL argument(s).");
		return;
	}

	// Free the Sprite object and nullify dangling pointer.
	free(*sprite);
	*sprite = NULL;
}

// Read the properties of a Sprite component from a file.
void SpriteRead(Sprite* sprite, Stream stream)
{
	if (sprite == NULL || stream == NULL) {
		TraceMessage("Error: SpriteRead received NULL argument(s).");
		return;
	}

	// Read frameIndex and transparency into sprite object.
	sprite->frameIndex = StreamReadInt(stream);
	sprite->alpha = StreamReadFloat(stream);
}

// Render a Sprite (Sprite can be textured or untextured).
void SpriteRender(const Sprite* sprite, Transform* transform)
{
	// Validate the Sprite and Sprite Mesh pointers.
	if (sprite == NULL || sprite->mesh == NULL || transform == NULL) {
		TraceMessage("Error: SpriteRender received NULL argument(s).");
		return;
	}

	if (sprite->spriteSource) {
		// If the Sprite has a valid SpriteSource,
		DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
		SpriteSourceSetTexture(sprite->spriteSource);
		SpriteSourceSetTextureOffset(sprite->spriteSource, sprite->frameIndex);
	}
	else {
		DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
	}

	DGL_Graphics_SetCB_Alpha(sprite->alpha);
	DGL_Graphics_SetCB_TintColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });

	if (sprite->text == NULL) {
		// If the sprite’s text pointer is NULL,
		const Matrix2D* matrix = TransformGetMatrix(transform);
		if (matrix == NULL) {
			TraceMessage("Error: TransformGetMatrix failed to retrieve matrix.");
			return;
		}
		DGL_Graphics_SetCB_TransformMatrix(matrix);
		MeshRender(sprite->mesh);
	}
	else {

		Matrix2D matrix = *TransformGetMatrix(transform);
		Matrix2D offset;
		const Vector2D* theTranslation = TransformGetTranslation(transform);
		Vector2D temp = *theTranslation;
		Matrix2DTranslate(&offset, temp.x, 0);

		// This variable will be used to “walk” through the string without modifying.
		const char* text = sprite->text;

		// While the local text pointer points at a non-zero character,
		while (text != NULL && *text != '\0') {

			unsigned frameIndex = *text - ' ';
			SpriteSourceSetTextureOffset(sprite->spriteSource, frameIndex);
			DGL_Graphics_SetCB_TransformMatrix(&matrix);
			MeshRender(sprite->mesh);
			text++;

			// Concatenate the translation matrix and transformation matrix.
			Matrix2DConcat(&matrix, &offset, &matrix);
		}
	}
}

// Get a Sprite's alpha value.
float SpriteGetAlpha(const Sprite* sprite)
{
	// Verify that arguements are valid.
	if (sprite == NULL) {
		TraceMessage("Error: SpriteGetAlpha received NULL argument(s).");
		return 0.0f;
	}

	return sprite->alpha;
}

// Set a Sprite's alpha value.
void SpriteSetAlpha(Sprite* sprite, float alpha)
{
	// Verify that arguments are valid.
	if (sprite == NULL) {
		TraceMessage("Error: SpriteSetAlpha received NULL argument(s).");
		return;
	}

	// Clamp the alpha value so that it stays in range.
	sprite->alpha = min(1.0f, max(0.0f, alpha));
}

// Set a Sprite's current frame.
void SpriteSetFrame(Sprite* sprite, unsigned int frameIndex)
{
	// Verify that arguments are valid.
	if (sprite == NULL) {
		TraceMessage("Error: SpriteSetFrame received NULL argument(s).");
		return;
	}

	// Verify frameIndex does not exceed total number of frames.
	unsigned totalFrames = SpriteSourceGetFrameCount(sprite->spriteSource);
	if (frameIndex <= totalFrames - 1 && frameIndex >= 0) {
		TraceMessage("Error: SpriteSetFrame received an invalid frame index = %d", frameIndex);
		return;
	}

	// Assign the frameIndex to sprite and run a trace message.
	sprite->frameIndex = frameIndex;
	TraceMessage("SpriteSetFrame: frame index = %d", frameIndex);
}

// Set the Sprite's mesh.
void SpriteSetMesh(Sprite* sprite, const Mesh* mesh)
{
	// Verify arguments are valid.
	if (sprite == NULL || mesh == NULL) {
		TraceMessage("Error: SpriteSetMesh received NULL argument(s).");
		return;
	}

	// Assign the mesh to the sprite.
	sprite->mesh = mesh;
}

// Set a new SpriteSource for the specified Sprite.
void SpriteSetSpriteSource(Sprite* sprite, const SpriteSource* spriteSource)
{
	// Verify arguments are valid.
	if (sprite == NULL) {
		TraceMessage("Error: SpriteSetSpriteSource received NULL argument(s).");
		return;
	}

	// Assign spriteSource to sprite.
	sprite->spriteSource = spriteSource;
}

// Assign a text string to a Sprite component.  This will allow a sequence of
void SpriteSetText(Sprite* sprite, const char* text)
{
	if (sprite == NULL) {
		TraceMessage("Error: SpriteSetText received NULL argument(s).");
		return;
	}

	sprite->text = text;
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

