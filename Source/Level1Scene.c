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
#include "Level2Scene.h"
#include "Stream.h"
#include "Trace.h"
#include "Mesh.h"
#include "SpriteSource.h"
#include "Entity.h"
#include "DGL.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

static const float groundHeight = -150.0f;
static const float moveVelocity = 500.0f;
static const float jumpVelocity = 1000.0f;
static const Vector2D gravityNormal = { 0.0f, -1500.0f };
static const Vector2D gravityNone = { 0.0f, 0.0f };

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level1Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	int numLives;
	Mesh* newMesh;
	SpriteSource* newSpriteSource;
	Entity* newEntity;

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
	0		// numLives
	,NULL	// Mesh*
	,NULL	// SpriteSource*
	,NULL	// Entity*
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
	// Open file path and save to Stream type variable.
	const char* filePath = "Data/Level1_Lives.txt";
	Stream fileStream = StreamOpen(filePath);

	if (fileStream == NULL) {
		TraceMessage("Error: fileStream for %s is NULL", filePath);
	}

	// Read initial value for numLives into variable.
	instance.numLives = StreamReadInt(fileStream);
	StreamClose(&fileStream);

	// Test Mesh* newMesh.
	instance.newMesh = MeshCreate();
	MeshBuildQuad(instance.newMesh, 0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");

	// Test SpriteSource* mySpriteSource.
	instance.newSpriteSource = SpriteSourceCreate();
	SpriteSourceLoadTexture(instance.newSpriteSource, 1, 1, "PlanetTexture.png");
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

	//instance.numLives -= 1;
	if (instance.numLives <= 0) {
		SceneSystemSetNext(Level2SceneGetInstance());
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

