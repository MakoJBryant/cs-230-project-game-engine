//------------------------------------------------------------------------------
//
// File Name:	StubSystem.c
// Author(s):	Mako J. Bryant (mako.bryant)
// Project:		Project 4
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

// Essentials.
#include "stdafx.h"
#include <Windows.h>

// Systems.
#include "BaseSystem.h"
#include "StubSystem.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct StubSystem
{
	// WARNING: The base class must always be included first.
	BaseSystem	base;

	// Add any system-specific variables second.

} StubSystem;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//  System-specific State functions:
static bool StubSystemInit(void);
static void StubSystemUpdate(float dt);
static void StubSystemRender(void);
static void StubSystemExit(void);

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static StubSystem instance =
{
	{ "StubSystem", StubSystemInit, StubSystemUpdate, StubSystemRender, StubSystemExit},
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Stub System.
// Returns:
//	 Pointer to the abstract BaseSystem for this derived System.
BaseSystem* StubSystemGetInstance()
{
	// Initialize any system-specific variables here:

	// Return a reference to the instance of this system.
	return (BaseSystem*)&instance;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Initialize the Stub System.
// Returns:
//   Return "true" if the system was initialized successfully, otherwise return "false".
static bool StubSystemInit(void)
{
	// Return false if the system was NOT initialized successfully.

	// Return true if the system was initialized successfully.
	return true;
}

// Update the Stub System.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void StubSystemUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);
}

// Render any objects associated with the Stub System.
static void StubSystemRender(void)
{
}

// Shutdown the Stub System.
//   (HINT: Free any allocated resources and/or close any opened files).
static void StubSystemExit(void)
{
}

