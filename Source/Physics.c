//------------------------------------------------------------------------------
//
// File Name:	Physics.c
// Author(s):	Mako J. Bryant (0068410)
// Project:		Project 2
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Physics.h"

#include "DGL.h" // Vector2D
#include "Trace.h"
#include "Stream.h" // StreamReadVector2D
#include "Vector2D.h" // Vector2DScaleAdd
#include "Transform.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Physics
{
	// Previous position.  May be used for resolving collisions.
	Vector2D	oldTranslation;

	// Acceleration = inverseMass * (sum of forces)
	Vector2D	acceleration;

	// Velocity may be stored as a direction vector and speed scalar, instead.
	Vector2D	velocity;

	// Used when calculating acceleration due to forces.
	// Used when resolving collision between two dynamic objects.
	//float		inverseMass;

} Physics;


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

// Dynamically allocate a new Physics component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
Physics* PhysicsCreate(void)
{
	// Create memory for object.
	Physics* newPhysics = (Physics*)calloc(1, sizeof(Physics));

	// Verify that memory was allocated successfully.
	if (newPhysics == NULL) {
		TraceMessage("Error: PhysicsCreate failed to allocated memory.");
		return NULL;
	}

	// Set default values.
	newPhysics->oldTranslation = (Vector2D){ 0.0f, 0.0f };
	newPhysics->acceleration = (Vector2D){ 0.0f, 0.0f };
	newPhysics->velocity = (Vector2D){ 0.0f, 0.0f };

	return newPhysics;
}

// Free the memory associated with a Physics component.
// (NOTE: The Physics pointer must be set to NULL.)
// Params:
//	 physics = Pointer to the Physics component pointer.
void PhysicsFree(Physics** physics)
{
	// Verify that arguments are valid.
	if (physics == NULL || *physics == NULL) {
		TraceMessage("Error: PhysicsFree received NULL argument(s).");
		return;
	}

	// Free object and nullify dangling pointer.
	free(*physics);
	*physics = NULL;
}

// Read the properties of a Physics component from a file.
// [NOTE: Read the acceleration and velocity values using StreamReadVector2D.]
// Params:
//	 physics = Pointer to the Physics component.
//	 stream = Pointer to the data stream used for reading.
void PhysicsRead(Physics* physics, Stream stream)
{
	// Verify that arguments are valid.
	if (physics == NULL || stream == NULL) {
		TraceMessage("Error: PhysicsRead received NULL argument(s).");
		return;
	}

	// Read the acc and vel values into the physics object.
	StreamReadVector2D(stream, &physics->acceleration);
	StreamReadVector2D(stream, &physics->velocity);
}

// Get the acceleration of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return a pointer to the component's acceleration structure,
//		else return a NULL pointer.
const Vector2D* PhysicsGetAcceleration(const Physics* physics)
{
	// Verify that arguments are valid.
	if (physics == NULL) {
		TraceMessage("Error: PhysicsGetAcceleration received NULL argument(s).");
		return NULL;
	}

	return &physics->acceleration;
}

// Get the velocity of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return a pointer to the component's velocity structure,
//		else return a NULL pointer.
const Vector2D* PhysicsGetVelocity(const Physics* physics)
{
	// Verify that arguments are valid.
	if (physics == NULL) {
		TraceMessage("Error: PhysicsGetVelocity received NULL argument(s).");
		return NULL;
	}

	return &physics->velocity;
}

// Get the old translation (position) of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return a pointer to the component's oldTranslation structure,
//		else return a NULL pointer.
const Vector2D* PhysicsGetOldTranslation(Physics* physics)
{
	// Verify that arguments are valid.
	if (physics == NULL) {
		TraceMessage("Error: PhysicsGetOldTranslation received NULL argument(s).");
		return NULL;
	}

	return &physics->oldTranslation;
}

// Set the acceleration of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
//	 acceleration = Pointer to an acceleration vector.
void PhysicsSetAcceleration(Physics* physics, const Vector2D* acceleration)
{
	// Verify that arguments are valid.
	if (physics == NULL || acceleration == NULL) {
		TraceMessage("Error: PhysicsSetAcceleration received NULL argument(s).");
		return;
	}

	physics->acceleration = *acceleration;
}

// Set the velocity of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
//	 velocity = Pointer to a velocity vector.
void PhysicsSetVelocity(Physics* physics, const Vector2D* velocity)
{
	// Verify that arguments are valid.
	if (physics == NULL || velocity == NULL) {
		TraceMessage("Error: PhysicsSetVelocity received NULL argument(s).");
		return;
	}

	physics->velocity = *velocity;
}

// Update the state of a Physics component using the Semi-Implicit Euler method,
//	 as outlined in the "Dynamics" lecture slides and the project instructions.
// (NOTE: This function must verify that the Physics and Transform pointers are valid.)
// (NOTE: Members cannot be accessed if their typedef struct is hidden in a source file.)
// Params:
//	 physics = Pointer to the physics component.
//	 transform = Pointer to the associated transform component.
//	 dt = Change in time (in seconds) since the last game loop.
void PhysicsUpdate(Physics* physics, Transform* transform, float dt)
{
	// Validate the pointers.
	if (physics == NULL || transform == NULL) {
		TraceMessage("Error: PhysicsUpdate received NULL argument(s).");
		return;
	}

	// Get translation from the transform component.
	const Vector2D* currentTranslation = TransformGetTranslation(transform);
	if (currentTranslation == NULL) {
		TraceMessage("Error: PhysicsUpdate failed to get current translation.");
		return;
	}

	// Set oldTranslation = translation.
	physics->oldTranslation = *currentTranslation;

	// Set velocity += acceleration * dt
	Vector2DScaleAdd(&physics->velocity, &physics->acceleration, dt, &physics->velocity);

	// Set translation += velocity * dt
	Vector2D newTranslation;
	Vector2DScaleAdd(&newTranslation, &physics->velocity, dt, currentTranslation);

	// Set translation on the transform component.
	TransformSetTranslation(transform, &newTranslation);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

