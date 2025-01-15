//------------------------------------------------------------------------------
//
// File Name:	Engine.c
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <assert.h>

#include "DGL.h"

#include "BaseSystem.h"
#include "Engine.h"
#include "Trace.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

enum { systemMax = 10 };

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct
{
	unsigned systemCount;
	BaseSystem* systems[systemMax];

} Engine;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static Engine engine = { 0 };

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Add a system to the game engine.
void EngineAddSystem(BaseSystemPtr system)
{
	// Verify that a valid system pointer has been passed.
	assert(system && "EngineAddSystem Error: A NULL system pointer has been passed.");

	// Verify that the system container size will not be exceeded.
	assert((engine.systemCount < systemMax) && "EngineAddSystem Error: The maximum container size has been exceeded.");

	// Add the new system to the system container.
	engine.systems[engine.systemCount++] = system;
}

// Initialize the game engine.
bool EngineInit()
{
	// Initialize the Tracing/Logging module.
	TraceInit();
	TraceMessage("Engine: Init");

	//--------------------------------------------------------------------------
	// Initialize all systems.
	//--------------------------------------------------------------------------

	for (unsigned i = 0; i < engine.systemCount; ++i)
	{
		BaseSystem* system = engine.systems[i];

		// Verify that the current system is valid.
		assert(system && "EngineInit Error: A NULL system has been added to the engine.");
		assert(system->init && "EngineInit Error: A system is missing an Init function.");

		// Write a trace message as each system is initialized.
		TraceMessage("%s: Init", system->name);

		// Call the current system's Init function.
		bool success = system->init();
		if (!success)
		{
			return FALSE;
		}
	}
	return true;
}

// Update the game engine.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void EngineUpdate(float dt)
{
	TraceMessage("Engine: Update");

	//--------------------------------------------------------------------------
	// Update all systems.
	//--------------------------------------------------------------------------

	for (unsigned i = 0; i < engine.systemCount; ++i)
	{
		BaseSystem* system = engine.systems[i];

		// Verify that the current system is valid.
		assert(system && "EngineUpdate Error: A NULL system has been added to the engine.");
		assert(system->update && "EngineUpdate Error: A system is missing an Update function.");

		// Write a trace message as each system is updated. [Intentionally disabled]
		//TraceMessage("%s: Update", system->name);

		// Call the current system's Update function.
		system->update(dt);
	}
}

void EngineRender()
{
	TraceMessage("Engine: Render");

	// Start the draw process for the current game loop.
	DGL_Graphics_StartDrawing();

	//--------------------------------------------------------------------------
	// Render all systems.
	//--------------------------------------------------------------------------

	for (unsigned i = 0; i < engine.systemCount; ++i)
	{
		BaseSystem* system = engine.systems[i];

		// Verify that the current system is valid.
		assert(system && "EngineUpdate Error: A NULL system has been added to the engine.");
		assert(system->render && "EngineRender Error: A system is missing a Render function.");

		// Write a trace message as each system is rendered. [Intentionally disabled]
		//TraceMessage("%s: Render", system->name);

		// Call the current system's Render function.
		system->render();
	}

	// Complete the draw process for the current game loop.
	DGL_Graphics_FinishDrawing();
}


// Shutdown the game engine.
void EngineExit()
{
	TraceMessage("Engine: Exit");

	//--------------------------------------------------------------------------
	// NOTE: Shutdown the systems in reverse order.
	//--------------------------------------------------------------------------

	for (int i = engine.systemCount - 1; i >= 0; --i)
	{
		BaseSystem* system = engine.systems[i];

		// Verify that the current system is valid.
		assert(system && "EngineExit Error: A NULL system has been added to the engine.");
		assert(system->exit && "EngineExit Error: A system is missing an Exit function.");

		// Write a trace message as each system is exited.
		TraceMessage("%s: Exit", system->name);

		// Call the current system's Exit function.
		system->exit();
	}

	// Shutdown the Tracing/Logging module.
	TraceShutdown();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
