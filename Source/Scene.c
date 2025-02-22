//------------------------------------------------------------------------------
//
// File Name:	Scene.c
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <assert.h>

#include "Scene.h"
#include "SceneSystem.h"

#include "Trace.h"
#include "EntityContainer.h"
#include "EntityFactory.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Typedefs:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
static EntityContainer* entities = NULL;
//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Verify that a scene is valid (no NULL pointers).
// Params:
//   scene	Pointer to the scene to be checked.
bool SceneIsValid(const Scene* scene)
{
	// This function should never be called with a "NULL" scene.
	assert(scene && "SceneIsValid Error: A NULL pointer was passed as a parameter.");

	if (scene->name && scene->load && scene->init && scene->update && scene->render && scene->exit && scene->unload)
	{
		return true;
	}

	return false;
}

// Load the scene.
void SceneLoad(const Scene* scene)
{
	// Verify that the function pointer is valid.
	if (scene && (scene->load != NULL))
	{
		// Call TraceMessage, passing the format string "%s: Load" and the name of the scene.
		TraceMessage("%s: Load", scene->name);

		// Initialize the entities variable by calling EntityContainerCreate.
		EntityContainerCreate();

		// Execute the Load function.
		(*scene->load)();
	}
}

// Initialize the scene.
void SceneInit(const Scene* scene)
{
	// Verify that the function pointer is valid.
	if (scene && (scene->init != NULL))
	{
		// TODO: Call TraceMessage, passing the format string "%s: Init" and the name of the scene.
		TraceMessage("%s: Init", scene->name);

		// Execute the Init function.
		(*scene->init)();
	}
}

// Update the scene.
void SceneUpdate(const Scene* scene, float dt)
{
	// Verify that the function pointer is valid.
	if (scene && (scene->update != NULL))
	{
		// Call TraceMessage, passing the format string "%s: Update" and the name of the scene.
		TraceMessage("%s: Update", scene->name);

		// Execute the Update function.
		(*scene->update)(dt);

		// Update any existing entities by calling EntityContainerUpdateAll.
		EntityContainerUpdateAll(entities, dt);
	}
}

// Render the scene.
void SceneRender(const Scene* scene)
{
	// Verify that the function pointer is valid.
	if (scene && (scene->render != NULL))
	{
		// Call TraceMessage, passing the format string "%s: Render" and the name of the scene.
		TraceMessage("%s: Render", scene->name);

		// Execute the Render function.
		(*scene->render)();

		// Render all entities within the scene by calling EntityContainerRenderAll.
		EntityContainerRenderAll(entities);
	}
}

// Exit the scene.
void SceneExit(const Scene* scene)
{
	// Verify that the function pointer is valid.
	if (scene && (scene->exit != NULL))
	{
		// TODO: Call TraceMessage, passing the format string "%s: Exit" and the name of the scene.
		TraceMessage("%s: Exit", scene->name);

		// Execute the Exit function.
		(*scene->exit)();

		// Free any existing entities by calling EntityContainerFreeAll and EntityFactoryFreeAll.
		EntityContainerFreeAll(entities);
		EntityFactoryFreeAll();
	}
}

// Unload the scene.
void SceneUnload(const Scene* scene)
{
	// Verify that the function pointer is valid.
	if (scene && (scene->unload != NULL))
	{
		// Call TraceMessage, passing the format string "%s: Unload" and the name of the scene.
		TraceMessage("%s: Unload", scene->name);

		// Execute the Unload function.
		(*scene->unload)();

		// Free the EntityContainer by calling EntityContainerFree.
		EntityContainerFree(&entities);
	}
}

// Restart the active scene.
void SceneRestart(void)
{
	// Tell the Scene System to restart the active scene.
	SceneSystemRestart();
}

// Add an Entity to the Scene.
// (NOTE: This is done by storing the Entity within an EntityContainer.)
// Params:
//   entity = Pointer to the Entity to be added.
void SceneAddEntity(Entity* entity)
{
	/// This new function should add an Entity to the EntityContainer’s list.
	EntityContainerAddEntity(entities, entity);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

