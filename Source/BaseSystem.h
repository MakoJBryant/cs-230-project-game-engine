//------------------------------------------------------------------------------
//
// File Name:	BaseSystem.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 0
// Course:		CS230S25
// Purpose:		This serves as a base "class" for all systems.
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

typedef bool(*FunctionPtrBoolVoid)(void);
typedef void(*FunctionPtrVoidVoid)(void);
typedef void(*FunctionPtrVoidFloat)(float dt);

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// The following two structures are equivalent.
// The first structure uses typedefs in an attempt to improve readability.
// The second structure is provided to show the implementation without typedefs.
#if 1
typedef struct BaseSystem
{
	const char* name;
	const FunctionPtrBoolVoid	init;	// Pointer to the derived system's Init function.
	const FunctionPtrVoidFloat	update;	// Pointer to the derived system's Update function.
	const FunctionPtrVoidVoid	render;	// Pointer to the derived system's Render function.
	const FunctionPtrVoidVoid	exit;	// Pointer to the derived system's Exit function.

} BaseSystem, *BaseSystemPtr;
#else
typedef struct BaseSystem
{
	bool(*init)(void);			// Pointer to the derived system's Init function.
	void(*update)(float dt);	// Pointer to the derived system's Update function.
	void(*render)(void);		// Pointer to the derived system's Render function.
	void(*exit)(void);			// Pointer to the derived system's Exit function.

} BaseSystem, *BaseSystemPtr;
#endif

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       // End of extern "C" {
#endif

