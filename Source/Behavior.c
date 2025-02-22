//------------------------------------------------------------------------------
//
// File Name:	Behavior.c
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
#include "Behavior.h"
#include "Trace.h"
#include "Stream.h"

// Components.
#include "Entity.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

#if 0

typedef void(*BehaviorFunctionPtr)(Behavior* behavior);
typedef void(*BehaviorFunctionPtrDt)(Behavior* behavior, float dt);

// This structure is being declared publicly, as it will be used to implement
// pseudo-inheritance in Project 5.
// NOTE: You are not allowed to change the contents of this structure, as it is
// part of the public interface.
typedef struct Behavior
{
	// Pointer to the behavior's parent entity.
	Entity* parent;

	// Behavior Finite-State Machine (FSM) state variables.
	int stateCurr;
	int stateNext;

	// Behavior Finite-State Machine (FSM) function pointers.
	BehaviorFunctionPtr		onInit;
	BehaviorFunctionPtrDt	onUpdate;
	BehaviorFunctionPtr		onExit;

	// Additional variables shared by all behaviors.
	// NOTE: Variables that are unique to a specific behavior should not be placed here.

	// Generic timer - may be used as a life timer or a weapon cooldown timer.
	// (Default = 0, means infinite amount of time remaining or weapon can be fired.)
	float	timer;

} Behavior;

#endif
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------


// Dynamically allocate a clone of an existing behavior.
// (Hint: Perform a shallow copy of the member variables.)
// Params:
//	 other = Pointer to the component to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned component,
//	   else return NULL.
Behavior* BehaviorClone(Behavior* other)
{
	TraceMessage("Error: BehaviorClone empty.");
	UNREFERENCED_PARAMETER(other);
	return NULL;
}

// Free the memory associated with a Behavior component.
// (Also, set the behavior pointer to NULL.)
// Params:
//	 behavior = Pointer to the Behavior component.
void BehaviorFree(Behavior** behavior)
{
	TraceMessage("Error: BehaviorFree empty.");
	UNREFERENCED_PARAMETER(behavior);
	return;
}

// Read the properties of a Behavior component from a file.
// [NOTE: Read the stateCurr and stateNext values using StreamReadInt.]
// [NOTE: Read the timer value using StreamReadFloat.]
// Params:
//	 behavior = Pointer to the Behavior component.
//	 stream = Pointer to the data stream used for reading.
void BehaviorRead(Behavior* behavior, Stream stream)
{
	TraceMessage("Error: BehaviorRead empty.");
	UNREFERENCED_PARAMETER(behavior);
	UNREFERENCED_PARAMETER(stream);
	return;
}

// Set the parent Entity for a Behavior component.
// Params:
//	 behavior = Pointer to the Behavior component.
//	 parent = Pointer to the parent Entity.
void BehaviorSetParent(Behavior* behavior, Entity* parent)
{
	TraceMessage("Error: BehaviorSetParent empty.");
	UNREFERENCED_PARAMETER(behavior);
	UNREFERENCED_PARAMETER(parent);
	return;
}

// Update the Behavior component.
// (Hint: Refer to the Word document for detailed instructions regarding this function.)
// Params:
//	 behavior = Pointer to the Behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorUpdate(Behavior* behavior, float dt)
{
	TraceMessage("Error: BehaviorUpdate empty.");
	UNREFERENCED_PARAMETER(behavior);
	UNREFERENCED_PARAMETER(dt);
	return;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

