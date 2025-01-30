//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.c
// Author(s):	Mako J. Bryant (0068410)
// Project:		Project 2
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "SpriteSource.h"
#include "DGL.h"
#include "Trace.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct SpriteSource
{
	// The dimensions of the sprite sheet.
	// (Hint: These should be initialized to (1, 1).)
	int	numRows;
	int	numCols;

	// Pointer to a texture resource created using the DigiPen Graphics Library (DGL).
	const DGL_Texture* texture;

} SpriteSource;

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

// Dynamically allocate a new SpriteSource object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (Hint: numRows and numCols should be initialized to 1.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
SpriteSource* SpriteSourceCreate()
{
	// Create memory for object.
	SpriteSource* newSpriteSource = (SpriteSource*)calloc(1, sizeof(SpriteSource));

	// Validate memory allocated correctly.
	if (newSpriteSource == NULL) {
		TraceMessage("SpriteSourceCreate: failed to allocate memory.");
		return NULL;
	}

	// Initialize default values.
	newSpriteSource->numRows = 1;
	newSpriteSource->numCols = 1;

	return newSpriteSource;
}

// Free the memory associated with a SpriteSource object.
// (NOTE: The DGL_Texture resource must be freed using DGL_Graphics_FreeTexture().)
// (NOTE: The SpriteSource object must be freed using free().
// (NOTE: The SpriteSource pointer must be set to NULL.)
// Params:
//	 spriteSource = Pointer to the SpriteSource pointer.
void SpriteSourceFree(SpriteSource** spriteSource)
{
	// Verify that arguments are valid (and pointer arguments).
	if (spriteSource == NULL || *spriteSource == NULL) {
		TraceMessage("SpriteSourceFree: arguments invalid.");
		return;
	}

	// Must dereference the (pointer to the pointer) before you can access the (pointer).
	// Free the texture resource.
	DGL_Graphics_FreeTexture(&(*spriteSource)->texture);

	// Free the object itself and nullify the dangling pointer.
	free(*spriteSource);
	*spriteSource = NULL;
}

// Load a texture from a file (may be an Col x Row sprite sheet).
// (NOTE: The folder path, "Assets/" should be prepended to the texture name before
//    opening the file.  The function sprintf_s can be used for this purpose.
//    https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/sprintf-s-sprintf-s-l-swprintf-s-swprintf-s-l)
// Params:
//	 numCols = The number of columns in the sprite sheet.
//	 numRows = The number of rows in the sprite sheet.
//	 textureName = The name of the texture to be loaded.
void SpriteSourceLoadTexture(SpriteSource* spriteSource, int numCols, int numRows, const char* textureName)
{
	// Verify that arguments are valid.
	if (spriteSource == NULL || textureName == NULL) {
		TraceMessage("SpriteSourceLoadTexture: arguments invalid.");
		return;
	}

	// Create file path from textureName string.
	char fullFilePath[256];
	sprintf_s(fullFilePath, sizeof(fullFilePath), "Assets/%s", textureName);
	TraceMessage("Graphics: Created %s texture file path", fullFilePath);

	// Load texture from file path.
	spriteSource->texture = DGL_Graphics_LoadTexture(fullFilePath);
	if (spriteSource->texture == NULL) {
		TraceMessage("SpriteSourceLoadTexture: failed to load texture.");
		return;
	}

	// Assign the texture (spritesheet) a number of rows and columns.
	spriteSource->numRows = numRows;
	spriteSource->numCols = numCols;
}

// Returns the maximum number of frames possible, given the dimensions of the sprite sheet.
// (Hint: Frame count = numCols * numRows.)
// Params:
//	 spriteSource = Pointer to the SpriteSource object.
// Returns:
//	 If the SpriteSource pointer is valid,
//		then return the calculated frame count (numCols * numRows),
//		else return 0.
unsigned SpriteSourceGetFrameCount(const SpriteSource* spriteSource)
{
	// Verify that arguments are valid.
	if (spriteSource == NULL) {
		TraceMessage("SpriteSourceGetFrameCount: arguments invalid.");
		return 0;
	}
	
	// Return the total frame count in the texture.
	unsigned totalFrameCount = spriteSource->numCols * spriteSource->numRows;
	return totalFrameCount;
}

// Returns the UV coordinates of the specified frame in a sprite sheet.
// (Hint: Refer to the Week 2 lecture slides for the correct calculations.)
// Params:
//	 spriteSource = Pointer to the SpriteSource object.
//	 frameIndex = A frame index within a sprite sheet.
//   u = Pointer to a float to contain the U coordinate. 
//   v = Pointer to a float to contain the V coordinate. 
void SpriteSourceGetUV(const SpriteSource* spriteSource, unsigned int frameIndex, float* u, float* v)
{

	// Verify that arguments are valid.
	if (spriteSource == NULL || u == NULL || v == NULL) {
		TraceMessage("SpriteSourceGetUV: arguments invalid.");
		return;
	}

	// Verify index trying to be accessed isn't bigger than the texture.
	if (frameIndex >= SpriteSourceGetFrameCount(spriteSource)) {
		TraceMessage("SpriteSourceGetUV: frameIndex invalid.");
		return;
	}

	// Convert values to find the position in terms of rows and columns.
	unsigned col = frameIndex % spriteSource->numCols;
	unsigned row = frameIndex / spriteSource->numCols;

	// Assign pointers to the UV coordinates of the specified frame.
	*u = (float)col / spriteSource->numCols;
	*v = (float)row / spriteSource->numRows;
}

// Sets a SpriteSource texture for rendering.
// Params:
//	 spriteSource = Pointer to the SpriteSource object.
void SpriteSourceSetTexture(const SpriteSource* spriteSource)
{
	// Verify that arguments are valid.
	if (spriteSource == NULL || spriteSource->texture == NULL) {
		TraceMessage("SpriteSource: arguments invalid.");
		return;
	}

	// Bind the texture to the graphics pipeline so that it can be used for rendering.
	DGL_Graphics_SetTexture(spriteSource->texture);
}

// Sets the texture UV offsets for rendering.
// Params:
//	 spriteSource = Pointer to the SpriteSource object.
void SpriteSourceSetTextureOffset(const SpriteSource* spriteSource, unsigned frameIndex)
{
	// Verify that arguments are valid.
	if (spriteSource == NULL || spriteSource->texture == NULL) {
		TraceMessage("SpriteSourceSetTextureOffset: arguments invalid.");
		return;
	}

	// Validate frameIndex isn't bigger than the total number of frames.
	unsigned totalFrames = spriteSource->numCols * spriteSource->numRows;
	if (frameIndex >= totalFrames) {
		TraceMessage("SpriteSourceSetTextureOffset: Invalid frameIndex.");
		return;
	}

	// Calculate UV coordinates to the specific frame.
	float u, v;
	SpriteSourceGetUV(spriteSource, frameIndex, &u, &v);

	// Set the texture offset and add it to the rendering pipeline.
	DGL_Vec2 textureOffset = { u, v };
	DGL_Graphics_SetCB_TextureOffset(&textureOffset);
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

