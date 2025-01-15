//------------------------------------------------------------------------------
//
// File Name:	SceneSystem.h
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

typedef struct BaseSystem BaseSystem;
typedef struct Scene Scene;

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Typedefs:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Scene System.
// Returns:
//	 Pointer to the abstract BaseSystem for this derived System.
BaseSystem* SceneSystemGetInstance(void);

// Check if the Scene System is still running (a scene is active).
// Returns:
//   bool	True is a scene is active, false otherwise.
bool SceneSystemIsRunning(void);

// Tell the Scene System to restart the active scene.
void SceneSystemRestart(void);

// Set a new active scene, replacing any existing active scene.
// Params:
//   scene	Pointer to the new scene.
void SceneSystemSetNext(const Scene* scene);

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       // End of extern "C" {
#endif

