//------------------------------------------------------------------------------
//
// File Name:	Level1Scene.c
// Author(s):	Mako J. Bryant (0068410)
// Project:		Project 1
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Scene.h"
#include "SceneSystem.h"
#include "Level1Scene.h"
#include "Stream.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level1Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	int numLives;

} Level1Scene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void Level1SceneLoad(void);
static void Level1SceneInit(void);
static void Level1SceneUpdate(float dt);
static void Level1SceneExit(void);
static void Level1SceneUnload(void);
static void Level1SceneRender(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level1Scene instance =
{
	// Initialize the base structure:
	{ "Level1", Level1SceneLoad, Level1SceneInit, Level1SceneUpdate, Level1SceneRender, Level1SceneExit, Level1SceneUnload },

	// Initialize any scene-specific variables:
	0 // numLives
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Stub Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* Level1SceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void Level1SceneLoad(void)
{
	// StreamOpen will check if filePath is valid for us.
	const char* filePath = "Data/Level1_Lives.txt";
	Stream fileStream = StreamOpen(filePath);

	// We check if fileStream is valid here.
	if (fileStream != NULL) {
		instance.numLives = StreamReadInt(fileStream);
		StreamClose(fileStream);
	} 
	else {
		// If NULL, send an error message to TraceMessage.
		TraceMessage("Error: fileStream for %s is NULL", filePath);
	}
}

// Initialize the entities and variables used by the scene.
static void Level1SceneInit()
{
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level1SceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);

	instance.numLives -= 1;
	if (instance.numLives <= 0) {
		SceneSystemSetNext("Level2");
	}
}

// Render any objects associated with the scene.
void Level1SceneRender(void)
{
}

// Free any objects associated with the scene.
static void Level1SceneExit()
{
}

// Unload any resources used by the scene.
static void Level1SceneUnload(void)
{
}

