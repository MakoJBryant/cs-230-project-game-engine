//------------------------------------------------------------------------------
//
// File Name:	Physics.c
// Author(s):	Mako J. Bryant (mako.bryant)
// Project:		Project 2
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
#include "Physics.h"
#include "DGL.h" // Vector2D
#include "Trace.h"
#include "Stream.h" // StreamReadVector2D
#include "Vector2D.h" // Vector2DScaleAdd

// Components.
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

	// Rotational velocity (added to handle rotational physics).
	float rotationalVelocity;

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
Physics* PhysicsCreate(void)
{
	// Create memory for object.
	Physics* newPhysics = calloc(1, sizeof(Physics));

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

// Dynamically allocate a clone of an existing Physics component.
Physics* PhysicsClone(const Physics* other)
{
	if (other == NULL) {
		TraceMessage("Error: PhysicsClone received NULL argument.");
		return NULL;
	}

	// Create new Physics object.
	Physics* newPhysics = PhysicsCreate();
	if (newPhysics == NULL) {
		TraceMessage("Error: PhysicsClone failed to allocate memory.");
		return NULL;
	}

	// Perform shallow copy of needed fields.
	newPhysics->oldTranslation = other->oldTranslation;
	newPhysics->acceleration = other->acceleration;
	newPhysics->velocity = other->velocity;
	newPhysics->rotationalVelocity = other->rotationalVelocity;

	return newPhysics;
}

// Free the memory associated with a Physics component.
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
const Vector2D* PhysicsGetVelocity(const Physics* physics)
{
	// Verify that arguments are valid.
	if (physics == NULL) {
		TraceMessage("Error: PhysicsGetVelocity received NULL argument(s).");
		return NULL;
	}

	return &physics->velocity;
}

// Get the rotational velocity of a physics component.
float PhysicsGetRotationalVelocity(const Physics* physics)
{
	if (physics == NULL) {
		TraceMessage("Error: PhysicsGetRotationalVelocity received NULL argument.");
		return 0.0f;
	}

	return physics->rotationalVelocity;
}


// Get the old translation (position) of a Physics component.
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
void PhysicsSetVelocity(Physics* physics, const Vector2D* velocity)
{
	// Verify that arguments are valid.
	if (physics == NULL || velocity == NULL) {
		TraceMessage("Error: PhysicsSetVelocity received NULL argument(s).");
		return;
	}

	physics->velocity = *velocity;
}

// Set the rotational velocity of a physics component.
void PhysicsSetRotationalVelocity(Physics* physics, float rotationalVelocity)
{
	if (physics == NULL) {
		TraceMessage("Error: PhysicsSetRotationalVelocity received NULL argument.");
		return;
	}

	physics->rotationalVelocity = rotationalVelocity;
}


// Update the state of a Physics component using the Semi-Implicit Euler method,
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

	// Get the current rotation value.
	float currentRotation = TransformGetRotation(transform);

	// Apply rotational velocity to the transform's rotation.
	float newRotation = currentRotation + physics->rotationalVelocity * dt;

	// Set the updated rotation.
	TransformSetRotation(transform, newRotation);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

