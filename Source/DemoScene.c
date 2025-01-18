//------------------------------------------------------------------------------
//
// File Name:	DemoScene.c
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "DGL.h"

#include "DemoScene.h"
#include "Scene.h"
#include "SceneSystem.h"

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct DemoScene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.

} DemoScene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

// TODO: Declare Constants:
// DGL_Color Constants:
static const DGL_Color DGL_Color_Black = { 0.0f, 0.0f, 0.0f, 1.0f };
static const DGL_Color DGL_Color_White = { 1.0f, 1.0f, 1.0f, 1.0f };
static const DGL_Color DGL_Color_Red = { 1.0f, 0.0f, 0.0f, 1.0f };
static const DGL_Color DGL_Color_Green = { 0.0f, 1.0f, 0.0f, 1.0f };
static const DGL_Color DGL_Color_Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
static const DGL_Color DGL_Color_Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
static const DGL_Color DGL_Color_Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
static const DGL_Color DGL_Color_Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };

// Constants used to display objects within the scene:
static const DGL_Vec2 posColored = { -200.f, 200.f };
static const DGL_Vec2 posTinted = { 200.f, 200.f };
static const DGL_Vec2 posTexturedBall = { -200.f, -200.f };
static const DGL_Vec2 posTexturedSquare = { 200.f, -200.f };

static const DGL_Vec2 scaleColored = { 100.f, 100.f };
static const DGL_Vec2 scaleTextured = { 100.f, 100.f };

// Constants used to move objects within the scene:
static const float cameraScrollSpeed = 2.0f;
static const float spaceshipScrollSpeed = 4.0f;
static const float uvScrollSpeed = 0.01f;
static const float rotationSpeed = 0.5f;

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

// TODO: Declare Variables:
// Variables used for referencing loaded assets.
static DGL_Mesh* meshColor = NULL;
static DGL_Mesh* meshTexture = NULL;
static DGL_Mesh* meshSpaceship = NULL;
static DGL_Mesh* meshLine = NULL;

static DGL_Texture* textureBall = NULL;
static DGL_Texture* textureSquare = NULL;

// Variables used for changing the scene.
static DGL_Vec2 posCamera = { 0, 0 };
static DGL_Vec2 posSpaceship = { 0.f, 0.f };

static DGL_Vec2 uvOffset = { 0.f, 0.f };

static float alpha = 1.0f;
static float rotation = 0.0f;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void DemoSceneLoad(void);
static void DemoSceneInit(void);
static void DemoSceneUpdate(float dt);
static void DemoSceneExit(void);
static void DemoSceneUnload(void);
static void DemoSceneRender(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static DemoScene instance =
{
	// Initialize the base structure:
	{ "Demo", DemoSceneLoad, DemoSceneInit, DemoSceneUpdate, DemoSceneRender, DemoSceneExit, DemoSceneUnload },

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Demo Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* DemoSceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void DemoSceneLoad(void)
{
	// TODO: Create Meshes:
	// Create a simple, colored mesh.
	DGL_Graphics_StartMesh();
	DGL_Graphics_AddTriangle(
		&(DGL_Vec2){ -0.5f, -0.5f }, &DGL_Color_Red, &(DGL_Vec2){ 0.0f, 0.0f },
		&(DGL_Vec2){  0.5f,  0.5f }, &DGL_Color_Green, &(DGL_Vec2){ 0.0f, 0.0f },
		&(DGL_Vec2){  0.5f, -0.5f }, &DGL_Color_Blue, &(DGL_Vec2){ 0.0f, 0.0f });
	DGL_Graphics_AddTriangle(
		&(DGL_Vec2){ -0.5f, -0.5f }, &DGL_Color_Cyan, &(DGL_Vec2){ 0.0f, 0.0f },
		&(DGL_Vec2){ -0.5f,  0.5f }, &DGL_Color_Magenta, &(DGL_Vec2){ 0.0f, 0.0f },
		&(DGL_Vec2){  0.5f,  0.5f }, &DGL_Color_Yellow, &(DGL_Vec2){ 0.0f, 0.0f });
	meshColor = DGL_Graphics_EndMesh();

	// Create a simple, textured mesh.
	DGL_Graphics_StartMesh();
	DGL_Graphics_AddTriangle(
		&(DGL_Vec2){ -0.5f, -0.5f }, &DGL_Color_Black, &(DGL_Vec2){ 0.0f, 1.0f },
		&(DGL_Vec2){  0.5f,  0.5f }, &DGL_Color_Black, &(DGL_Vec2){ 1.0f, 0.0f },
		&(DGL_Vec2){  0.5f, -0.5f }, &DGL_Color_Black, &(DGL_Vec2){ 1.0f, 1.0f });
	DGL_Graphics_AddTriangle(
		&(DGL_Vec2){ -0.5f, -0.5f }, &DGL_Color_Black, &(DGL_Vec2){ 0.0f, 1.0f },
		&(DGL_Vec2){ -0.5f,  0.5f }, &DGL_Color_Black, &(DGL_Vec2){ 0.0f, 0.0f },
		&(DGL_Vec2){  0.5f,  0.5f }, &DGL_Color_Black, &(DGL_Vec2){ 1.0f, 0.0f });
	meshTexture = DGL_Graphics_EndMesh();

	// Create a triangular, colored mesh.
	DGL_Graphics_StartMesh();
	DGL_Graphics_AddTriangle(
		&(DGL_Vec2){  0.5f,  0.0f }, &DGL_Color_Yellow, &(DGL_Vec2){ 0.0f, 0.0f },
		&(DGL_Vec2){ -0.5f, -0.5f }, &DGL_Color_Red, &(DGL_Vec2){ 0.0f, 0.0f },
		&(DGL_Vec2){ -0.5f,  0.5f }, &DGL_Color_Red, &(DGL_Vec2){ 0.0f, 0.0f });
	meshSpaceship = DGL_Graphics_EndMesh();

	DGL_Graphics_StartMesh();
	DGL_Graphics_AddVertex(&(DGL_Vec2){  0.5f,  0.5f }, &DGL_Color_White, &(DGL_Vec2){ 0.0f, 0.0f });
	DGL_Graphics_AddVertex(&(DGL_Vec2){ -0.5f,  0.5f }, &DGL_Color_White, &(DGL_Vec2){ 0.0f, 0.0f });
	DGL_Graphics_AddVertex(&(DGL_Vec2){ -0.5f, -0.5f }, &DGL_Color_White, &(DGL_Vec2){ 0.0f, 0.0f });
	DGL_Graphics_AddVertex(&(DGL_Vec2){  0.5f, -0.5f }, &DGL_Color_White, &(DGL_Vec2){ 0.0f, 0.0f });
	DGL_Graphics_AddVertex(&(DGL_Vec2){  0.5f,  0.5f }, &DGL_Color_White, &(DGL_Vec2){ 0.0f, 0.0f });
	meshLine = DGL_Graphics_EndMesh();

	// TODO: Load/Create Textures:
	textureBall = DGL_Graphics_LoadTexture("Assets/ball.png");

	// Create a 2x2 texture from memory.
	const unsigned char colorsSquare[16] =
	{
		255,   0,   0, 255,
		  0, 255,   0, 255,
		  0,   0, 255, 255,
		255, 255, 255, 255
	};
	textureSquare = DGL_Graphics_LoadTextureFromMemory(colorsSquare, 2, 2);

}

// Initialize the entities and variables used by the scene.
static void DemoSceneInit()
{
	// TODO: Add code to set the following variables to their starting values.
	//   posCamera
	//   posSpaceship
	//   uvOffset
	//   alpha
	//   rotation

	posCamera.x = 0;
	posCamera.y = 0;
	posSpaceship.x = 0.f;
	posSpaceship.y = 0.f;

	uvOffset.x = 0.f;
	uvOffset.y = 0.f;

	alpha = 1.0f;
	rotation = 0.0f;

	// TODO: Set the background color and blend mode.
	DGL_Graphics_SetBackgroundColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);

}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void DemoSceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);

	// Update the scene.
	if (DGL_Window_HasFocus())
	{
		// TODO: Update the camera's position.
		if (DGL_Input_KeyDown('A'))
		{
			posCamera.x -= cameraScrollSpeed;
		}
		else if (DGL_Input_KeyDown('D'))
		{
			posCamera.x += cameraScrollSpeed;
		}
		if (DGL_Input_KeyDown('W'))
		{
			posCamera.y += cameraScrollSpeed;
		}
		else if (DGL_Input_KeyDown('S'))
		{
			posCamera.y -= cameraScrollSpeed;
		}

		// TODO: Update the triangular ("Spaceship") mesh's position.
		if (DGL_Input_KeyDown(VK_UP))
			posSpaceship.y += spaceshipScrollSpeed;
		else if (DGL_Input_KeyDown(VK_DOWN))
			posSpaceship.y -= spaceshipScrollSpeed;
		if (DGL_Input_KeyDown(VK_LEFT))
			posSpaceship.x -= spaceshipScrollSpeed;
		else if (DGL_Input_KeyDown(VK_RIGHT))
			posSpaceship.x += spaceshipScrollSpeed;

		// TODO: Update the triangular ("Spaceship") mesh's Alpha value.
		if (DGL_Input_KeyDown('Z'))
		{
			alpha = max(0.0f, alpha - 0.02f);
		}
		else if (DGL_Input_KeyDown('X'))
		{
			alpha = min(1.0f, alpha + 0.02f);
		}

		// TODO: Update the Ball texture's UV offsets.
		if (DGL_Input_KeyDown('J'))
			uvOffset.x -= uvScrollSpeed;
		else if (DGL_Input_KeyDown('L'))
			uvOffset.x += uvScrollSpeed;
		if (DGL_Input_KeyDown('I'))
			uvOffset.y -= uvScrollSpeed;
		else if (DGL_Input_KeyDown('K'))
			uvOffset.y += uvScrollSpeed;

		// TODO: Update the rotation value.
		rotation += rotationSpeed * dt;

		// TODO: Add code to restart the level when the ‘0’ key is triggered (when the key changes state from not pressed to pressed).
		if (DGL_Input_KeyTriggered('0')) {
			SceneSystemRestart();
		}

	}
}

// Render any objects associated with the scene.
void DemoSceneRender(void)
{
	// TODO: Update the camera's position every frame.
	DGL_Camera_SetPosition(&posCamera);

	// TODO: Display a simple, colored mesh.
	DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
	DGL_Graphics_SetTexture(NULL);
	DGL_Graphics_SetCB_Alpha(1.0f);
	DGL_Graphics_SetCB_TintColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });
	DGL_Graphics_SetCB_TransformData(&posColored, &scaleColored, 0.f);
	DGL_Graphics_DrawMesh(meshColor, DGL_DM_TRIANGLELIST);

	// TODO: Draw a simple, colored mesh with a red (50%) tint.
	DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
	DGL_Graphics_SetCB_Alpha(1.0f);
	DGL_Graphics_SetCB_TintColor(&(DGL_Color) { 1.0f, 0.0f, 0.0f, 0.5f });
	DGL_Graphics_SetCB_TransformData(&posTinted, &scaleColored, rotation);
	DGL_Graphics_DrawMesh(meshColor, DGL_DM_TRIANGLELIST);

	// TODO: Draw a simple, textured mesh using the Ball texture.
	DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
	DGL_Graphics_SetTexture(textureBall);
	DGL_Graphics_SetCB_Alpha(1.0f);
	DGL_Graphics_SetCB_TextureOffset(&uvOffset);
	DGL_Graphics_SetCB_TintColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });
	DGL_Graphics_SetCB_TransformData(&posTexturedBall, &scaleTextured, 0.f);
	DGL_Graphics_DrawMesh(meshTexture, DGL_DM_TRIANGLELIST);

	// TODO: Draw a simple, textured mesh using the 2x2 texture.
	DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
	DGL_Graphics_SetTextureSamplerData(DGL_TSM_POINT, DGL_AM_WRAP);
	DGL_Graphics_SetTexture(textureSquare);
	DGL_Graphics_SetCB_Alpha(1.0f);
	DGL_Graphics_SetCB_TextureOffset(&(DGL_Vec2) { 0.f, 0.f });
	DGL_Graphics_SetCB_TintColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });
	DGL_Graphics_SetCB_TransformData(&posTexturedSquare, &scaleTextured, 0.f);
	DGL_Graphics_DrawMesh(meshTexture, DGL_DM_TRIANGLELIST);
	DGL_Graphics_SetTextureSamplerData(DGL_TSM_LINEAR, DGL_AM_WRAP);

	// TODO: Draw a triangular, colored mesh.
	DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
	DGL_Graphics_SetCB_Alpha(alpha);
	DGL_Graphics_SetCB_TintColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });
	DGL_Graphics_SetCB_TransformData(&posSpaceship, &scaleColored, 0.f);
	DGL_Graphics_DrawMesh(meshSpaceship, DGL_DM_TRIANGLELIST);

	// TODO: Draw a 4-segment line strip.
	DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
	DGL_Graphics_SetCB_Alpha(1.0f);
	DGL_Graphics_SetCB_TintColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });
	DGL_Graphics_SetCB_TransformData(&(DGL_Vec2) { 0.f, 0.f }, & (DGL_Vec2) { 800.f, 600.f }, 0.f);
	DGL_Graphics_DrawMesh(meshLine, DGL_DM_LINESTRIP);

}

// Free any objects associated with the scene.
static void DemoSceneExit()
{
}

// Unload any resources used by the scene.
static void DemoSceneUnload(void)
{
	// TODO: Free all meshes
	DGL_Graphics_FreeMesh(&meshColor);
	DGL_Graphics_FreeMesh(&meshTexture);
	DGL_Graphics_FreeMesh(&meshSpaceship);
	DGL_Graphics_FreeMesh(&meshLine);

	// TODO: Free all textures
	DGL_Graphics_FreeTexture(&textureBall);
	DGL_Graphics_FreeTexture(&textureSquare);

}

