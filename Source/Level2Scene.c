//------------------------------------------------------------------------------
//
// File Name:	Level2Scene.c
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
#include "Level2Scene.h"
#include "Stream.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level2Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	int numLives;
	int numHealth;

} Level2Scene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void Level2SceneLoad(void);
static void Level2SceneInit(void);
static void Level2SceneUpdate(float dt);
static void Level2SceneExit(void);
static void Level2SceneUnload(void);
static void Level2SceneRender(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level2Scene instance =
{
	// Initialize the base structure:
	{ "Stub", Level2SceneLoad, Level2SceneInit, Level2SceneUpdate, Level2SceneRender, Level2SceneExit, Level2SceneUnload },

	// Initialize any scene-specific variables:
	0, // numLives
	0 // numHealth
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Stub Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* Level2SceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void Level2SceneLoad(void)
{
	// Open file path and save to Stream type variable.
	const char* filePath = "Data/Level2_Lives.txt";
	Stream fileStream = StreamOpen(filePath);

	if (fileStream != NULL) {
		// Read initial value for numLives into variable.
		instance.numLives = StreamReadInt(fileStream);
		StreamClose(fileStream);
	}
	else {
		// If NULL, send an error message.
		TraceMessage("Error: fileStream for %s is NULL", filePath);
	}
}

// Initialize the entities and variables used by the scene.
static void Level2SceneInit()
{
	// Open file path and save to Stream type variable.
	const char* filePath = "Data/Level2_Health.txt";
	Stream fileStream = StreamOpen(filePath);

	if (fileStream != NULL) {
		// Read initial value for numHealth into variable.
		instance.numHealth = StreamReadInt(fileStream);
		StreamClose(fileStream);
	}
	else {
		// If NULL, send an error message.
		TraceMessage("Error: fileStream for %s is NULL", filePath);
	}
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level2SceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);

	// NOTE: This call causes the engine to exit immediately.  Make sure to remove
	//   it when you are ready to test out a new scene.
	SceneSystemSetNext(NULL);

	instance.numHealth -= 1;
	if (instance.numHealth <= 0) {

		instance.numLives -= 1;
		if (instance.numLives > 0) {
			// Restart scene.
			SceneSystemRestart();

		}
		else {
			// Change scene to "Sandbox".
			SceneSystemSetNext("Sandbox");

		}
	}
}

// Render any objects associated with the scene.
void Level2SceneRender(void)
{
}

// Free any objects associated with the scene.
static void Level2SceneExit()
{
}

// Unload any resources used by the scene.
static void Level2SceneUnload(void)
{
}

