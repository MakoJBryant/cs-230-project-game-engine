//------------------------------------------------------------------------------
//
// File Name:	SceneSystem.c
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <Windows.h>
#include <assert.h>

#include "BaseSystem.h"
#include "Level1Scene.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "StubScene.h"
#include "Trace.h"

//------------------------------------------------------------------------------
// Libraries
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct Scene Scene;

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct SceneSystem
{
	// WARNING: The base class must always be included first.
	BaseSystem	base;

	// Add any system-specific variables second.
	const Scene* activeScene;
	const Scene* nextScene;
	bool isRestarting;

} SceneSystem;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//  System-specific State functions:
static bool SceneSystemInit(void);
static void SceneSystemUpdate(float dt);
static void SceneSystemRender(void);
static void SceneSystemExit(void);

static bool SceneSystemIsChanging(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static SceneSystem instance =
{
	{ "SceneSystem", SceneSystemInit, SceneSystemUpdate, SceneSystemRender, SceneSystemExit},
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Scene System.
// Returns:
//	 Pointer to the abstract BaseSystem for this derived System.
BaseSystem* SceneSystemGetInstance()
{
	// Initialize any system-specific variables here:

	// Return a reference to the instance of this system.
	return (BaseSystem*)&instance;
}

// Check if the Scene System is still running (a scene is active).
// Returns:
//   bool	True is a scene is active, false otherwise.
bool SceneSystemIsRunning(void)
{
	return (instance.activeScene || instance.nextScene);
}

// Instruct the Scene System to restart the active scene.
void SceneSystemRestart(void)
{
	instance.isRestarting = true;
}

// Set a new active scene, replacing any existing active scene.
// Params:
//   scene	Pointer to the new scene.
void SceneSystemSetNext(const Scene* scene)
{
	if (scene == instance.activeScene) {
		// If the scene is the same as the active scene, restart the scene.
		SceneSystemRestart();
	}
	else {
		// If it's a different scene, set the nextScene as usual.
		if (scene) {
			assert(SceneIsValid(scene) && "SceneSystemSetNext Error: A scene is missing one or more functions.");
		}
		instance.nextScene = scene;
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Initialize the Scene System.
// Returns:
//   Return "true" if the system was initialized successfully, otherwise return "false".
static bool SceneSystemInit(void)
{
	// Set the starting (Default) scene.
	SceneSystemSetNext(Level1SceneGetInstance());

	return true;
}

// Update the Scene System.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void SceneSystemUpdate(float dt)
{
	// Scene changing?
	if (SceneSystemIsChanging())
	{
		// Exit active scene.
		SceneExit(instance.activeScene);

		/* TODO: Add support for Load and Unload. */
		// Scene restarting?
		if (instance.isRestarting == true) {
			// Clear restart flag.
			instance.isRestarting = false;
		}
		else {
			// Unload active scene.
			SceneUnload(instance.activeScene);
			// Change the active scene.
			instance.activeScene = instance.nextScene;
			// Load (new) active scene.
			SceneLoad(instance.activeScene);
		}
		// Initialize (new) active scene.
		SceneInit(instance.activeScene);
	}
	// Update the active scene.
	SceneUpdate(instance.activeScene, dt);
}

// Render any objects associated with the Scene system.
static void SceneSystemRender(void)
{
	// Render the active scene.
	SceneRender(instance.activeScene);
}

// Shutdown the Scene System.
//   (HINT: Free any allocated resources and/or opened files).
static void SceneSystemExit(void)
{
}

// Check if it is time to change scenes or restart the existing scene.
// Returns:
//   Returns "true" if a change request has been received, otherwise returns "false".
static bool SceneSystemIsChanging(void)
{
	return (instance.isRestarting || (instance.activeScene != instance.nextScene));
}

