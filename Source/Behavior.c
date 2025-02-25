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
// Params:
//   other = Pointer to the component to be cloned.
// Returns:
//   If 'other' is valid and the memory allocation was successful,
//   return a pointer to the cloned component, else return NULL.
Behavior* BehaviorClone(Behavior* other)
{
	if (other == NULL) {
		TraceMessage("Error: BehaviorClone received NULL argument(s).");
		return NULL;
	}

	// Allocate memory for the new Behavior.
	Behavior* newBehavior = (Behavior*)calloc(1, sizeof(Behavior));
	if (!newBehavior) {
		TraceMessage("Error: BehaviorClone failed to allocate memory.");
		return NULL;
	}

	// Perform a shallow copy of all member variables.
	*newBehavior = *other;

	// Set the parent Entity for the new behavior.
	if (newBehavior->parent) {
		EntityAddBehavior(newBehavior->parent, newBehavior);
	}

	return newBehavior;
}

// Free the memory associated with a Behavior component.
void BehaviorFree(Behavior** behavior)
{
	if (behavior == NULL || *behavior == NULL) {
		TraceMessage("Error: BehaviorFree received NULL argument(s).");
		return;
	}

	// Free the memory allocated for the behavior.
	free(*behavior);
	*behavior = NULL;
}

// Read the properties of a Behavior component from a file.
void BehaviorRead(Behavior* behavior, Stream stream)
{
	if (behavior == NULL || stream == NULL) {
		TraceMessage("Error: BehaviorRead received NULL argument(s).");
		return;
	}

	// Read the state values.
	behavior->stateCurr = StreamReadInt(stream);
	behavior->stateNext = StreamReadInt(stream);

	// Read the timer value.
	behavior->timer = StreamReadFloat(stream);
}

// Set the parent Entity for a Behavior component.
void BehaviorSetParent(Behavior* behavior, Entity* parent)
{
	if (behavior == NULL) {
		TraceMessage("Error: BehaviorSetParent received NULL argument(s).");
		return;
	}

	// Set the parent of the behavior.
	behavior->parent = parent;

	// Add this behavior to the entity.
	if (parent != NULL) {
		EntityAddBehavior(parent, behavior);
	}
}

// Update the Behavior component.
void BehaviorUpdate(Behavior* behavior, float dt)
{
	if (behavior == NULL) {
		TraceMessage("Error: BehaviorUpdate received NULL argument(s).");
		return;
	}

	// Check if state is changing.
	if (behavior->stateCurr != behavior->stateNext) {

		if (behavior->onExit != NULL) {
			behavior->onExit(behavior);
		}

		// Update the current state to the next state.
		behavior->stateCurr = behavior->stateNext;

		if (behavior->onInit != NULL) {
			behavior->onInit(behavior);
		}
	}

	if (behavior->onUpdate != NULL) {
		behavior->onUpdate(behavior, dt);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

