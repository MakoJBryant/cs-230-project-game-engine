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
#include "EntityFactory.h"
#include "Sprite.h"
#include "Physics.h"
#include "Transform.h"

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

static void Level1SceneMovementController(Entity* entity);

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
	// Create Planet Entity.
	instance.newEntity = EntityFactoryBuild("./Data/PlanetJump.txt");
	if (instance.newEntity == NULL) {
		return;
	}

	// Get Sprite component.
	Sprite* newSprite = EntityGetSprite(instance.newEntity);
	if (newSprite == NULL) {
		return;
	}

	// Set Sprite components.
	SpriteSetMesh(newSprite, instance.newMesh);
	SpriteSetSpriteSource(newSprite, instance.newSpriteSource);
	SpriteSetFrame(newSprite, 0); // for tracemessage testing

	// General settings.
	DGL_Graphics_SetBackgroundColor(&(DGL_Color) { 1.0f, 1.0f, 1.0f, 1.0f });
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level1SceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);

	Level1SceneMovementController(instance.newEntity);
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

static void Level1SceneMovementController(Entity* entity)
{
	// Get the Physics and Transform components from the Entity.
	Physics* newPhysics = EntityGetPhysics(entity);
	Transform* newTransform = EntityGetTransform(entity);
	if (newPhysics == NULL || newTransform == NULL) {
		return;
	}

	// Handle moving left or right.
	const Vector2D* currentVelocity = (PhysicsGetVelocity(newPhysics));
	Vector2D velocity = *currentVelocity; // Modifiable non-const copy.

	if (DGL_Input_KeyDown(VK_LEFT)) {
		// If LEFT ARROW key is pressed, set velocity.x = - moveVelocity.
		velocity.x = -moveVelocity;
		PhysicsSetVelocity(newPhysics, currentVelocity);
	}
	else if (DGL_Input_KeyDown(VK_RIGHT)) {
		// If RIGHT ARROW key is pressed, set velocity.x = moveVelocity.
		velocity.x = moveVelocity;
		PhysicsSetVelocity(newPhysics, currentVelocity);
	}
	else {
		// If neither is pressed, set velocity.x = 0.
		velocity.x = 0;
		PhysicsSetVelocity(newPhysics, currentVelocity);
	}

	// Handle Jumping.
	const Vector2D* currentAcceleration = (PhysicsGetAcceleration(newPhysics));
	Vector2D newAcceleration = *currentAcceleration;

	if (DGL_Input_KeyTriggered(VK_UP)) {
		velocity.y = jumpVelocity;
		newAcceleration = gravityNormal;
		PhysicsSetAcceleration(newPhysics, &newAcceleration);
	}

	// Handle Landing.
	const Vector2D* currentTranslation = TransformGetTranslation(newTransform);
	if (currentTranslation->y < groundHeight) {

		// Set y-axis translation value to groundHeight.
		Vector2D newTranslation = *currentTranslation;
		newTranslation.y = groundHeight;
		TransformSetTranslation(newTransform, &newTranslation);

		// Stop any y-axis velocity.
		velocity.y = 0;

		// Stop any acceleration.
		const Vector2D* newGravityNone = &gravityNone;
		PhysicsSetAcceleration(newPhysics, newGravityNone);

		// Lose a life and check death parameters.
		instance.numLives -= 1;
		if (instance.numLives <= 0) {
			SceneSystemSetNext(Level2SceneGetInstance());
		}
	}

	// After landing calculations, update velocity.
	PhysicsSetVelocity(newPhysics, &velocity);
}