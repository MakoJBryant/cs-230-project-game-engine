//------------------------------------------------------------------------------
//
// File Name:	Scene.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {	// Assume C declarations for C++.
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Typedefs:
//------------------------------------------------------------------------------

typedef void(*SceneFunctionVoidVoid)(void);
typedef void(*SceneFunctionVoidFloat)(float dt);

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// Structure to store the scene-specific State function pointers.
typedef struct Scene
{
	const char* name;
	SceneFunctionVoidVoid	load;
	SceneFunctionVoidVoid	init;
	SceneFunctionVoidFloat	update;
	SceneFunctionVoidVoid	render;
	SceneFunctionVoidVoid	exit;
	SceneFunctionVoidVoid	unload;
} Scene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Verify that a scene is valid (no NULL pointers).
// Params:
//   scene	Pointer to the scene to be checked.
bool SceneIsValid(const Scene* scene);

// Functions for executing the scene-specific State functions.
void SceneLoad(const Scene* scene);
void SceneInit(const Scene* scene);
void SceneUpdate(const Scene* scene, float dt);
void SceneRender(const Scene* scene);
void SceneExit(const Scene* scene);
void SceneUnload(const Scene* scene);

// Restart the active scene.
void SceneRestart(void);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       // End of extern "C" {
#endif

