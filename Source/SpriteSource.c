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
	SpriteSource* newSpriteSource = (SpriteSource*)calloc(1, sizeof(SpriteSource));

	if (newSpriteSource == NULL) {
		TraceMessage("Graphics: SpriteSourceCreate() memory allocation FAILED.");
		return NULL;
	}

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
	if (spriteSource == NULL) {
		TraceMessage("Graphics: SpriteSourceFree() FAILED.");
		return;
	}

	// Must dereference the (pointer to the pointer) before you can access the (pointer).
	DGL_Graphics_FreeTexture(&(*spriteSource)->texture);

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
	// Validate arguments passed.
	if (spriteSource == NULL || textureName == NULL) {
		TraceMessage("Graphics: SpriteSourceLoadTexture arguments invalid.");
		return;
	}

	// Create file path from textureName.
	char fullFilePath[256];
	strcpy_s(fullFilePath, _countof(fullFilePath), "Assets/");
	strcat_s(fullFilePath, _countof(fullFilePath), textureName);
	TraceMessage("Graphics: Created %s texture file path", fullFilePath);

	// Load texture from file path.
	spriteSource->texture = DGL_Graphics_LoadTexture(fullFilePath);
	if (spriteSource->texture == NULL) {
		TraceMessage("Graphics: SpriteSourceLoadTexture failed to load texture.");
		return;
	}

	// Assign spritesheet/texture a number of rows and columns.
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
	UNREFERENCED_PARAMETER(spriteSource);
	return 0;
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
	UNREFERENCED_PARAMETER(frameIndex);
	UNREFERENCED_PARAMETER(spriteSource);
	UNREFERENCED_PARAMETER(u);
	UNREFERENCED_PARAMETER(v);
}

// Sets a SpriteSource texture for rendering.
// Params:
//	 spriteSource = Pointer to the SpriteSource object.
void SpriteSourceSetTexture(const SpriteSource* spriteSource)
{
	// Validate arguments passed.
	if (spriteSource == NULL || spriteSource->texture == NULL) {
		TraceMessage("Graphics: Invalid SpriteSource or texture.");
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
	// Validate arguments passed.
	if (spriteSource == NULL || spriteSource->texture == NULL) {
		TraceMessage("Graphics: Invalid SpriteSource or texture.");
		return;
	}

	// Validate frameIndex isn't bigger than the total number of frames.
	unsigned totalFrames = spriteSource->numCols * spriteSource->numRows;
	if (frameIndex >= totalFrames) {
		TraceMessage("Graphics: Invalid frameIndex.");
		return;
	}

	// Calculate the row and column of the offset frame.
	unsigned row = frameIndex / spriteSource->numCols;
	unsigned col = frameIndex % spriteSource->numCols;
	
	// Calculate the UV coordinates for this frame.
	float uStart = (float)col / spriteSource->numCols;
	float vStart = (float)row / spriteSource->numRows;

	// Create a DGL_Vec2 structure for the texture offset.
	DGL_Vec2 textureOffset = { uStart, vStart };

	// Update the pipeline so that only the correct part of the sprite sheet is rendered.
	DGL_Graphics_SetCB_TextureOffset(&textureOffset);
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

