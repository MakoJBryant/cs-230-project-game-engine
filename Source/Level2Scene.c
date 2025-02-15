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
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "SandboxScene.h"
#include "DemoScene.h"
#include "Stream.h"
#include "Trace.h"
#include "Mesh.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "DGL.h"
#include "Sprite.h"
#include "Transform.h"
#include "Vector2D.h"
#include "Physics.h"

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
	Mesh* spaceshipMesh;
	Entity* spaceshipEntity;

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

static void Level2SceneMovementController(Entity* entity);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level2Scene instance =
{
	// Initialize the base structure:
	{ "Level2", Level2SceneLoad, Level2SceneInit, Level2SceneUpdate, Level2SceneRender, Level2SceneExit, Level2SceneUnload },

	// Initialize any scene-specific variables:
	 NULL	// spaceshipMesh
	,NULL	// spaceshipEntity
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
	instance.spaceshipMesh = MeshCreate();
	MeshBuildSpaceship(instance.spaceshipMesh);

}

// Initialize the entities and variables used by the scene.
static void Level2SceneInit()
{
	// Initialize spaceship entity.
	instance.spaceshipEntity = EntityFactoryBuild("./Data/SpaceshipHoming.txt");
	if (instance.spaceshipEntity == NULL) {
		return;
	}

	// Get Sprite, Set Mesh.
	Sprite* newSprite = EntityGetSprite(instance.spaceshipEntity);
	if (newSprite == NULL) {
		return;
	}
	SpriteSetMesh(newSprite, instance.spaceshipMesh);

	// General settings.
	DGL_Graphics_SetBackgroundColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f });
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level2SceneUpdate(float dt)
{
	// Update and display the spaceship Entity.
	Level2SceneMovementController(instance.spaceshipEntity);
	EntityUpdate(instance.spaceshipEntity, dt);

	// Get Sprite, Set Mesh.
	Sprite* newSprite = EntityGetSprite(instance.spaceshipEntity);
	if (newSprite == NULL) {
		return;
	}

	if (DGL_Input_KeyTriggered('Z')) {
		// If the user triggers the ‘Z’ key, set Spaceship sprite’s alpha value = 0.5f.
		SpriteSetAlpha(newSprite, 0.5f);
	}
	if (DGL_Input_KeyTriggered('X')) {
		// If the user triggers the ‘X’ key, set Spaceship sprite’s alpha value = 1.0f.
		SpriteSetAlpha(newSprite, 1.0f);
	}
}

// Render any objects associated with the scene.
void Level2SceneRender(void)
{
	EntityRender(instance.spaceshipEntity);
}

// Free any objects associated with the scene.
static void Level2SceneExit()
{
	EntityFree(&instance.spaceshipEntity);
}

// Unload any resources used by the scene.
static void Level2SceneUnload(void)
{
	MeshFree(&instance.spaceshipMesh);
}

static void Level2SceneMovementController(Entity* entity) 
{
	// Get the Physics and Transform components from the Entity.
	Physics* newPhysics = EntityGetPhysics(entity);
	Transform* newTransform = EntityGetTransform(entity);
	if (newPhysics == NULL || newTransform == NULL) {
		return;
	}

	// Get the mouse cursor position (in screen coordinates).
	Vector2D mousePosition = DGL_Input_GetMousePosition();
	// Convert the screen coordinates to world coordinates.
	mousePosition = DGL_Camera_ScreenCoordToWorld(&mousePosition);

	// Get the spaceship’s current translation.
	const Vector2D* spaceshipTranslation = TransformGetTranslation(newTransform);

	// Calculate a direction vector from the spaceship to the mouse position.
	Vector2D directionVector = { 0.0f, 0.0f };
	Vector2DSub(&directionVector, &mousePosition, spaceshipTranslation); // ERROR?
	Vector2DNormalize(&directionVector, &directionVector);

	// Set the transform’s rotation to convert the direction vector into an angle (in radians).
	float rotation = Vector2DToAngleRad(&directionVector);
	TransformSetRotation(newTransform, rotation);

	/// Set the Physics component’s velocity = direction vector * spaceshipSpeed.
	Vector2DScale(&directionVector, &directionVector, spaceshipSpeed);
	PhysicsSetVelocity(newPhysics, &directionVector);
}
