//------------------------------------------------------------------------------
//
// File Name:	Level1Scene.c
// Author(s):	Mako J. Bryant (0068410)
// Project:		Project 1
// Course:		CS230S25
//
// Copyright � 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

// Essentials.
#include "stdafx.h"
#include "Scene.h"
#include "Stream.h"
#include "Trace.h"
#include "DGL.h"

// Components.
#include "Entity.h"
#include "EntityFactory.h"
#include "Mesh.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Physics.h"
#include "Transform.h"
#include "Animation.h"

// Scenes.
#include "SceneSystem.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "SandboxScene.h"
#include "DemoScene.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

typedef enum MonkeyStates
{
	MonkeyInvalid = -1,
	MonkeyIdle,
	MonkeyWalk,
	MonkeyJump

} MonkeyStates;
enum MonkeyStates monkeyState = MonkeyInvalid;

static const float groundHeight = -150.0f;
static const float moveVelocity = 500.0f;
static const float jumpVelocity = 1000.0f;
static const float wallDistance = 462.0f;
static const float CheckSquareDistance = (75.0f * 75.0f);
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
	Mesh* planetMesh;
	Mesh* myMesh3x3;
	Mesh* myMesh16x8;
	Mesh* livesTextMesh;
	SpriteSource* planetSpriteSource;
	SpriteSource* monkeyIdleSpriteSource;
	SpriteSource* monkeyJumpSpriteSource;
	SpriteSource* monkeyWalkSpriteSource;
	SpriteSource* robotoMonoBlackSpriteSource;
	SpriteSource* livesTextSpriteSource;
	Entity* planetEntity;
	Entity* monkeyEntity;
	Entity* livesTextEntity;

} Level1Scene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

char livesBuffer[16];
char name[32];

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
static void Level1SceneSetMonkeyState(Entity* entity, MonkeyStates newState);
static void Level1SceneBounceController(Entity* entity);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level1Scene instance =
{
	// Initialize the base structure:
	{ "Level1", Level1SceneLoad, Level1SceneInit, Level1SceneUpdate, Level1SceneRender, Level1SceneExit, Level1SceneUnload },

	// Initialize any scene-specific variables:
	0		// numLives
	,NULL	// planetMesh
	,NULL	// myMesh3x3
	,NULL	// myMesh16x8
	,NULL	// livesTextMesh
	,NULL	// planetSpriteSource
	,NULL	// monkeyIdleSpriteSource
	,NULL	// monkeyJumpSpriteSource
	,NULL	// monkeyWalkSpriteSource
	,NULL	// robotoMonoBlackSpriteSource
	,NULL	// livesTextSpriteSource
	,NULL	// planetEntity
	,NULL	// monkeyEntity
	,NULL	// livesTextEntity
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

	// Create the planet.
	instance.planetMesh = MeshCreate(); // planet mesh
	MeshBuildQuad(instance.planetMesh, 0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");
	instance.planetSpriteSource = SpriteSourceCreate(); // planet sprite source
	SpriteSourceLoadTexture(instance.planetSpriteSource, 1, 1, "PlanetTexture.png");

	// Create the monkey meshes.
	instance.myMesh3x3 = MeshCreate(); // 3x3 mesh
	MeshBuildQuad(instance.myMesh3x3, 0.5f, 0.5f, 1.0f / 3, 1.0f / 3, "Mesh3x3");
	instance.myMesh16x8 = MeshCreate(); // 16x8 mesh
	MeshBuildQuad(instance.myMesh16x8, 0.5f, 0.5f, 1.0f / 16, 1.0f / 8, "Mesh16x8");

	// Create the monkey sprite sources.
	instance.monkeyIdleSpriteSource = SpriteSourceCreate(); // 1x1 monkey idle
	SpriteSourceLoadTexture(instance.monkeyIdleSpriteSource, 1, 1, "MonkeyIdle.png");
	instance.monkeyJumpSpriteSource = SpriteSourceCreate(); // 1x1 monkey jump
	SpriteSourceLoadTexture(instance.monkeyJumpSpriteSource, 1, 1, "MonkeyJump.png");
	instance.monkeyWalkSpriteSource = SpriteSourceCreate(); // 3x3 monkey walk
	SpriteSourceLoadTexture(instance.monkeyWalkSpriteSource, 3, 3, "MonkeyWalk.png");
	instance.robotoMonoBlackSpriteSource = SpriteSourceCreate(); // 16x8 roboto mono black
	SpriteSourceLoadTexture(instance.robotoMonoBlackSpriteSource, 16, 8, "Roboto_Mono_Black.png");

}

// Initialize the entities and variables used by the scene.
static void Level1SceneInit()
{
	// Create a �Planet� Entity.
	instance.planetEntity = EntityFactoryBuild("./Data/PlanetBounce.txt");
	if (instance.planetEntity == NULL) {
		return;
	}

	// Create a �Monkey� Entity.
	instance.monkeyEntity = EntityFactoryBuild("./Data/Monkey.txt");
	if (instance.monkeyEntity == NULL) {
		return;
	}
	monkeyState = MonkeyInvalid; // Initialize the monkeyState variable to �MonkeyInvalid�
	Level1SceneSetMonkeyState(instance.monkeyEntity, MonkeyIdle);

	// Create a �LivesText� Entity.
	instance.livesTextEntity = EntityFactoryBuild("./Data/MonkeyLivesText.txt");
	if (instance.livesTextEntity == NULL) {
		return;
	}
	Sprite* livesSprite = EntityGetSprite(instance.livesTextEntity); // Get the Entity�s Sprite.
	if (livesSprite == NULL) {
		return;
	}
	SpriteSetMesh(livesSprite, instance.livesTextMesh); // Set the Sprite�s Mesh
	SpriteSetSpriteSource(livesSprite, instance.livesTextSpriteSource); // and SpriteSource
	sprintf_s(livesBuffer, sizeof(livesBuffer), "Lives: %d", instance.numLives); // write text to livesBuffer
	SpriteSetText(livesSprite, livesBuffer); // Call SpriteSetText(), passing the livesBuffer.

	// General settings.
	DGL_Graphics_SetBackgroundColor(&(DGL_Color) { 1.0f, 1.0f, 1.0f, 1.0f }); // white
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level1SceneUpdate(float dt)
{
	// Update the planet Entity.
	Level1SceneMovementController(instance.planetEntity);
	EntityUpdate(instance.planetEntity, dt);

	// Level management controls.
	if (DGL_Input_KeyTriggered('1')) {
		SceneSystemRestart();
	}
	else if (DGL_Input_KeyTriggered('2')) {
		SceneSystemSetNext(Level2SceneGetInstance());
	}
	else if (DGL_Input_KeyTriggered('9')) {
		SceneSystemSetNext(SandboxSceneGetInstance());
	}
	else if (DGL_Input_KeyTriggered('0')) {
		SceneSystemSetNext(DemoSceneGetInstance());
	}
}

// Render any objects associated with the scene.
void Level1SceneRender(void)
{
	EntityRender(instance.planetEntity);
}

// Free any objects associated with the scene.
static void Level1SceneExit()
{
	EntityFree(&instance.planetEntity);
	EntityFree(&instance.monkeyEntity);

}

// Unload any resources used by the scene.
static void Level1SceneUnload(void)
{
	SpriteSourceFree(&instance.planetSpriteSource);
	SpriteSourceFree(&instance.monkeyIdleSpriteSource);
	SpriteSourceFree(&instance.monkeyJumpSpriteSource);
	SpriteSourceFree(&instance.monkeyWalkSpriteSource);
	SpriteSourceFree(&instance.robotoMonoBlackSpriteSource);

	MeshFree(&instance.planetMesh);
	MeshFree(&instance.myMesh3x3);
	MeshFree(&instance.myMesh16x8);

}

// Allows entities to move.
static void Level1SceneMovementController(Entity* entity)
{
	// Get the Physics and Transform components from the Entity.
	Physics* newPhysics = EntityGetPhysics(entity);
	Transform* newTransform = EntityGetTransform(entity);
	if (newPhysics == NULL || newTransform == NULL) {
		return;
	}

	// Handle moving left or right.
	Vector2D velocity = *PhysicsGetVelocity(newPhysics);
	if (DGL_Input_KeyDown(VK_LEFT)) { // left arrow key
		velocity.x = -moveVelocity;
		if (monkeyState != MonkeyJump) {
			Level1SceneSetMonkeyState(entity, MonkeyWalk);
		}
	}
	else if (DGL_Input_KeyDown(VK_RIGHT)) { // right arrow key
		velocity.x = moveVelocity;
		if (monkeyState != MonkeyJump) {
			Level1SceneSetMonkeyState(entity, MonkeyWalk);
		}
	}
	else { 
		velocity.x = 0;
		if (monkeyState != MonkeyJump) {
			Level1SceneSetMonkeyState(entity, MonkeyIdle);
		}
	}

	// Handle jumping.
	if (DGL_Input_KeyTriggered(VK_UP)) { // up arrow key
		velocity.y = jumpVelocity;
		PhysicsSetAcceleration(newPhysics, &gravityNormal);
		Level1SceneSetMonkeyState(entity, MonkeyJump);
	}

	// Handle landing.
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

		// Set monkey state to idle upon landing.
		Level1SceneSetMonkeyState(entity, MonkeyIdle);
	}

	// After landing calculations, update velocity.
	PhysicsSetVelocity(newPhysics, &velocity);
}

// For managing the �Monkey� Entity�s current state and animation.
static void Level1SceneSetMonkeyState(Entity* entity, MonkeyStates newState)
{
	// If (monkeyState != newState),
	if (monkeyState != newState)
	{
		// Set monkeyState = newState.
		monkeyState = newState;

		// Get the Entity�s Sprite and Animation components.
		Sprite* sprite = EntityGetSprite(entity);
		Animation* animation = EntityGetAnimation(entity);
		if (!sprite || !animation) {
			return;
		}

		switch (newState) 
		{
		case MonkeyIdle:
			SpriteSetMesh(sprite, instance.planetMesh); // Set the Sprite�s Mesh to the 1x1 mesh.
			SpriteSetSpriteSource(sprite, instance.monkeyIdleSpriteSource); // Set the Sprite�s SpriteSource to �MonkeyIdle�.
			AnimationPlay(animation, 1, 0.0f, false); // Call AnimationPlay with a frame count of 1, a frame duration of 0.0f, and looping = false.
			break;

		case MonkeyWalk:
			SpriteSetMesh(sprite, instance.myMesh3x3); // Set the Sprite�s Mesh to the 3x3 mesh.
			SpriteSetSpriteSource(sprite, instance.monkeyWalkSpriteSource); // Set the Sprite�s SpriteSource to �MonkeyWalk�.
			AnimationPlay(animation, 8, 0.05f, true); // Call AnimationPlay with a frame count of 8, a frame duration of 0.05f, and looping = true.
			break;

		case MonkeyJump:
			SpriteSetMesh(sprite, instance.planetMesh); // Set the Sprite�s Mesh to the 1x1 mesh.
			SpriteSetSpriteSource(sprite, instance.monkeyJumpSpriteSource); // Set the Sprite�s SpriteSource to �MonkeyJump�.
			AnimationPlay(animation, 1, 0.0f, false); // Call AnimationPlay with a frame count of 1, a frame duration of 0.0f, and looping = false.
			break;

		default:
			break;
		}
	}
}

// Bouncing logic for the Planet entity.
static void Level1SceneBounceController(Entity* entity)
{
	// Get the Physics and Transform components from the Entity.
	Physics* newPhysics = EntityGetPhysics(entity);
	Transform* newTransform = EntityGetTransform(entity);
	if (newPhysics == NULL || newTransform == NULL) {
		return;
	}

	// Get local copies of the Entity�s current position and velocity.
	Vector2D* currentPosition = TransformGetTranslation(newTransform);
	Vector2D velocity = *PhysicsGetVelocity(newPhysics);

	if (currentPosition->x <= -wallDistance) {
		currentPosition->x = -wallDistance;  // Constrain position to the left wall
		velocity.x = -velocity.x;  // Reverse velocity.x for bouncing effect
	}

	if (currentPosition->x >= wallDistance) {
		currentPosition->x = wallDistance;  // Constrain position to the right wall
		velocity.x = -velocity.x;  // Reverse velocity.x for bouncing effect
	}

	if (currentPosition->y <= groundHeight) {
		currentPosition->y = groundHeight + (groundHeight - currentPosition->y); // Note: This calculation is necessary to conserve energy
		velocity.y = -velocity.y;  // Reverse velocity.y for bouncing effect
	}

	// Store the Entity�s new position and velocity.
	TransformSetTranslation(newTransform, currentPosition);
	PhysicsSetVelocity(newPhysics, &velocity);
}

