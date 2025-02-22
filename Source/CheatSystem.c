//------------------------------------------------------------------------------
//
// File Name:	CheatSystem.c
// Author(s):	Mako J. Bryant (mako.bryant)
// Project:		Project 0
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
#include <Windows.h>
#include "DGL.h"

// Systems.
#include "BaseSystem.h"
#include "CheatSystem.h"
#include "SceneSystem.h"

// Components.
#include "Scene.h"

// Scenes.
#include "DemoScene.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "AsteroidsScene.h"
#include "SandboxScene.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct CheatSystem
{
	// WARNING: The base class must always be included first.
	BaseSystem	base;

	// Add any system-specific variables second.

} CheatSystem;

typedef struct
{
	char key;
	const Scene* (*getInstance)(void);

} CheatSystemKeyBinding;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//  System-specific State functions:
static bool CheatSystemInit(void);
static void CheatSystemUpdate(float dt);
static void CheatSystemRender(void);
static void CheatSystemExit(void);

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static CheatSystem instance =
{
	{ "CheatSystem", CheatSystemInit, CheatSystemUpdate, CheatSystemRender, CheatSystemExit},
};

// Define keyBindings with corresponding keys and scene instances.
static const CheatSystemKeyBinding keyBindings[] = {
	{ '1', Level1SceneGetInstance },
	{ '2', Level2SceneGetInstance },
	{ '3', AsteroidsSceneGetInstance },
	{ '9', SandboxSceneGetInstance },
	{ '0', DemoSceneGetInstance }
};
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Stub System.
// Returns:
//	 Pointer to the abstract BaseSystem for this derived System.
BaseSystem* CheatSystemGetInstance()
{
	// Initialize any system-specific variables here:

	// Return a reference to the instance of this system.
	return (BaseSystem*)&instance;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Initialize the Stub System.
// Returns:
//   Return "true" if the system was initialized successfully, otherwise return "false".
static bool CheatSystemInit(void)
{
	// Return false if the system was NOT initialized successfully.

	// Return true if the system was initialized successfully.
	return true;
}

// Update the Stub System.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void CheatSystemUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	// Iterate over keyBindings to check for pressed keys.
	for (size_t i = 0; i < sizeof(keyBindings) / sizeof(keyBindings[0]); ++i)
	{
		if (DGL_Input_KeyTriggered(keyBindings[i].key))
		{
			SceneSystemSetNext(keyBindings[i].getInstance());
			return; // Exit after setting scene.
		}
	}
}

// Render any objects associated with the Stub System.
static void CheatSystemRender(void)
{
}

// Shutdown the Stub System.
//   (HINT: Free any allocated resources and/or close any opened files).
static void CheatSystemExit(void)
{
}

