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

#include "stdafx.h"

#include "Sprite.h"
#include "DGL.h"
#include "Trace.h"
#include "SpriteSource.h"
#include "Transform.h"
#include "Stream.h"
#include "Mesh.h"

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
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (NOTE: You must initialize the 'alpha' member variable to 1.0f.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
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
// (NOTE: The Sprite pointer must be set to NULL.)
// Params:
//	 sprite = Pointer to the Sprite pointer.
void SpriteFree(Sprite** sprite)
{
	// Verify that arguments are valid (and pointer arguments).
	if (sprite == NULL || *sprite == NULL) {
		TraceMessage("Error: SpriteFree received NULL argument(s).");
		return;
	}

	// Free the Sprite object and nullify dangling pointer.
	free(*sprite);
	*sprite = NULL;
}

// Read the properties of a Sprite component from a file.
// [NOTE: Read the frameIndex value using StreamReadInt.]
// [NOTE: Read the alpha value using StreamReadFloat.]
// Params:
//	 sprite = Pointer to the Sprite component.
//	 stream = The data stream used for reading.
void SpriteRead(Sprite* sprite, Stream stream)
{
	// Verify that arguments are valid.
	if (sprite == NULL || stream == NULL) {
		TraceMessage("Error: SpriteRead received NULL argument(s).");
		return;
	}

	// Read frameIndex and transparency into sprite object.
	sprite->frameIndex = StreamReadInt(stream);
	sprite->alpha = StreamReadFloat(stream);
}

// Render a Sprite (Sprite can be textured or untextured).
// Params:
//	 sprite = Pointer to the Sprite component.
//   transform = Pointer to the Transform component.
void SpriteRender(const Sprite* sprite, Transform* transform)
{
	// Verify that arguments are valid.
	if (sprite == NULL || transform == NULL) {
		TraceMessage("Error: SpriteRender received NULL argument(s).");
		return;
	}

	if (sprite->spriteSource == NULL) {
		// Prepare to render untextured sprite.
		DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);

	}
	if (sprite->spriteSource != NULL) {
		// Prepare to render a textured sprite.
		DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);

		// Assign the texture via SpriteSource.
		SpriteSourceSetTexture(sprite->spriteSource);
		SpriteSourceSetTextureOffset(sprite->spriteSource, sprite->frameIndex);

	} 

	// Express settings for the rendered sprite.
	DGL_Graphics_SetCB_TransformData(
		 TransformGetTranslation(transform)		// position
		,TransformGetScale(transform)			// scale
		,TransformGetRotation(transform)		// rotation
	);
	DGL_Graphics_SetCB_Alpha(sprite->alpha);	// transparency
	DGL_Graphics_SetCB_TintColor(&(DGL_Color) 
		{ 1.0f, 0.0f, 0.0, 0.0f });				// tint color (red)
	
	// Render the mesh (list of triangles).
	MeshRender(sprite->mesh);
}

// Get a Sprite's alpha value.
// Params:
//	 sprite = Pointer to the Sprite component.
// Returns:
//	 If the pointer is valid,
//		then return the Sprite's alpha value (a value between 0.0f and 1.0f),
//		else return 0.0f.
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
// (NOTE: Make sure to clamp the resulting alpha value between 0.0f and 1.0f, as the
//	input value might be outside of this range.)
// (HINT: The min() and max() macros can be combined to create a clamp function.)
// Params:
//	 sprite = Pointer to the Sprite component.
//   alpha = The Sprite's new alpha value.
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
// (NOTE: You must verify that the frameIndex parameter is within the
//	range [0 to frame count - 1] before changing the Sprite's frame index!)
// Params:
//	 sprite = Pointer to the Sprite component.
//   frameIndex = New frame index for the Sprite (0 .. frame count - 1).
// ADDITIONAL REQUIREMENTS:
// - This function must make the following function call:
//     TraceMessage("SpriteSetFrame: frame index = %d", frameIndex);
void SpriteSetFrame(Sprite* sprite, unsigned int frameIndex)
{
	// Verify that arguments are valid.
	if (sprite == NULL) {
		TraceMessage("Error: SpriteSetFrame received NULL argument(s).");
		return;
	}

	// Verify frameIndex does not exceed total number of frames.
	unsigned totalFrames = SpriteSourceGetFrameCount(sprite->spriteSource);
	if (frameIndex >= totalFrames || frameIndex < 0) {
		TraceMessage("Error: SpriteSetFrame received an invalid frame index = %d", frameIndex);
		return;
	}

	// Assign the frameIndex to sprite and run a trace message.
	sprite->frameIndex = frameIndex;
	TraceMessage("SpriteSetFrame: frame index = %d", frameIndex);
}

// Set the Sprite's mesh.
// (NOTE: This mesh may be textured or untextured.)
// (NOTE: This mesh may contain any number of triangles.)
// Params:
//	 sprite = Pointer to the Sprite component.
//   mesh = Pointer to a Mesh object.
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
// (NOTE: The spriteSource parameter may be NULL.  This will remove an existing
//	texture from a Sprite and cause the Sprite to be displayed as a colored mesh.)
// Params:
//	 sprite = Pointer to the Sprite component.
//	 spriteSource = Pointer to a SpriteSource (this pointer may be NULL).
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

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

