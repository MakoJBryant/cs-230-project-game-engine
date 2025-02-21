//------------------------------------------------------------------------------
//
// File Name:	Behavior.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 4
// Course:		CS230S25
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct Entity Entity;
typedef struct Behavior Behavior;
typedef FILE* Stream;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
// Public Variables:
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
Behavior* BehaviorClone(Behavior* other);

// Free the memory associated with a Behavior component.
// (Also, set the behavior pointer to NULL.)
// Params:
//	 behavior = Pointer to the Behavior component.
void BehaviorFree(Behavior* * behavior);

// Read the properties of a Behavior component from a file.
// [NOTE: Read the stateCurr and stateNext values using StreamReadInt.]
// [NOTE: Read the timer value using StreamReadFloat.]
// Params:
//	 behavior = Pointer to the Behavior component.
//	 stream = Pointer to the data stream used for reading.
void BehaviorRead(Behavior* behavior, Stream stream);

// Set the parent Entity for a Behavior component.
// Params:
//	 behavior = Pointer to the Behavior component.
//	 parent = Pointer to the parent Entity.
void BehaviorSetParent(Behavior* behavior, Entity* parent);

// Update the Behavior component.
// (Hint: Refer to the Word document for detailed instructions regarding this function.)
// Params:
//	 behavior = Pointer to the Behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorUpdate(Behavior* behavior, float dt);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

