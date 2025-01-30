//------------------------------------------------------------------------------
//
// File Name:	Level2Scene.c
// Author(s):	Mako J. Bryant (0068410)
// Project:		Project 1
// Course:		CS230S25
//
// Copyright � 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Scene.h"
#include "SceneSystem.h"
#include "Level2Scene.h"
#include "SandboxScene.h"
#include "Stream.h"
#include "Trace.h"
#include "Mesh.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "DGL.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

static const float spaceshipSpeed = 500.0f;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level2Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	Mesh* newMesh;
	Entity* newEntity;

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
	{ "Level2", Level2SceneLoad, Level2SceneInit, Level2SceneUpdate, Level2SceneRender, Level2SceneExit, Level2SceneUnload },

	// Initialize any scene-specific variables:
	 NULL	// newMesh
	,NULL	// newEntity
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
	// Load spaceship mesh.
	instance.newMesh = MeshCreate();
	MeshBuildSpaceship(instance.newMesh);

}

// Initialize the entities and variables used by the scene.
static void Level2SceneInit()
{
	// Initialize spaceship entity.
	instance.newEntity = EntityFactoryBuild("./Data/SpaceshipHoming.txt");
	if (instance.newEntity == NULL) {
		return;
	}

	// Get Sprite, Set Mesh.
	Sprite* newSprite = EntityGetSprite(instance.newEntity);
	if (newSprite == NULL) {
		return;
	}
	//SpriteSetMesh(newSprite, instance.newMesh);

	// General settings.
	DGL_Graphics_SetBackgroundColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f });
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level2SceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);


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

