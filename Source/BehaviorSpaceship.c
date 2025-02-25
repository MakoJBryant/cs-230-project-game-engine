//------------------------------------------------------------------------------
//
// File Name:	BehaviorSpaceship.c
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

// Essential.
#include "stdafx.h"
#include "BehaviorSpaceship.h"
#include "Trace.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "DGL.h"
#include "Vector2D.h"

// Systems.
#include "EntityFactory.h"
#include "EntityContainer.h"

// Components.
#include "Entity.h"
#include "Behavior.h"
#include "Physics.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
typedef enum
{
    cSpaceshipInvalid = -1,
    cSpaceshipIdle,
    cSpaceshipThrust
} SpaceshipState;

static const float spaceshipAcceleration = 150.0f;
static const float spaceshipSpeedMax = 500.0f;
static const float spaceshipTurnRateMax = M_PI / 1.5f;
static const float spaceshipWeaponCooldownTime = 0.034f;
static const float spaceshipWeaponBulletSpeed = 750.0f;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
static void BehaviorSpaceshipOnInit(Behavior* behavior);
static void BehaviorSpaceshipOnUpdate(Behavior* behavior, float dt);
static void BehaviorSpaceshipOnExit(Behavior* behavior);
static void BehaviorSpaceshipUpdateRotation(Behavior* behavior, float dt);
static void BehaviorSpaceshipUpdateVelocity(Behavior* behavior, float dt);
static void BehaviorSpaceshipUpdateWeapon(Behavior* behavior, float dt);
static void BehaviorSpaceshipSpawnBullet(Behavior* behavior);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new (Spaceship) behavior component.
Behavior* BehaviorSpaceshipCreate(void)
{
    // Allocate memory for the new spaceship behavior
    Behavior* newBehavior = (Behavior*)calloc(1, sizeof(Behavior));
    if (newBehavior == NULL) {
        TraceMessage("Error: BehaviorSpaceshipCreate failed to allocate memory.");
        return NULL;
    }

    // Set initial state
    newBehavior->stateCurr = cSpaceshipInvalid;
    newBehavior->stateNext = cSpaceshipInvalid;

    // Assign function pointers
    newBehavior->onInit = BehaviorSpaceshipOnInit;
    newBehavior->onUpdate = BehaviorSpaceshipOnUpdate;
    newBehavior->onExit = BehaviorSpaceshipOnExit;

    return newBehavior;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Initialize the spaceship behavior.
static void BehaviorSpaceshipOnInit(Behavior* behavior)
{
    UNREFERENCED_PARAMETER(behavior);
    return;
}

// Update the spaceship behavior.
static void BehaviorSpaceshipOnUpdate(Behavior* behavior, float dt)
{
    switch (behavior->stateCurr)
    {
    case cSpaceshipIdle:
        BehaviorSpaceshipUpdateRotation(behavior, dt);
        BehaviorSpaceshipUpdateWeapon(behavior, dt);

        if (DGL_Input_KeyDown(VK_UP)) {
            behavior->stateNext = cSpaceshipThrust;
        }
        break;

    case cSpaceshipThrust:
        BehaviorSpaceshipUpdateRotation(behavior, dt);
        BehaviorSpaceshipUpdateVelocity(behavior, dt);
        BehaviorSpaceshipUpdateWeapon(behavior, dt);

        if (!DGL_Input_KeyDown(VK_UP)) {
            behavior->stateNext = cSpaceshipIdle;
        }
        break;
    }
}

// Exit the spaceship behavior.
static void BehaviorSpaceshipOnExit(Behavior* behavior)
{
    UNREFERENCED_PARAMETER(behavior);
    return;
}

// Update the spaceship's rotation based on input.
static void BehaviorSpaceshipUpdateRotation(Behavior* behavior, float dt)
{
    Entity* parent = behavior->parent;
    if (!parent) return;

    Physics* physics = EntityGetPhysics(parent);
    if (!physics) return;

    if (DGL_Input_KeyDown(VK_LEFT)) {
        PhysicsSetRotationalVelocity(physics, spaceshipTurnRateMax);
    }
    else if (DGL_Input_KeyDown(VK_RIGHT)) {
        PhysicsSetRotationalVelocity(physics, -spaceshipTurnRateMax);
    }
    else {
        PhysicsSetRotationalVelocity(physics, 0.0f);
    }
}

// Update the spaceship's velocity.
static void BehaviorSpaceshipUpdateVelocity(Behavior* behavior, float dt)
{
    // Get the parent entity.
    Entity* parent = behavior->parent;
    if (!parent) return;

    // Get the transform and physics components from the parent entity.
    Transform* transform = EntityGetTransform(parent);
    Physics* physics = EntityGetPhysics(parent);
    if (!transform || !physics) return;

    // Get the spaceship's rotation (in radians).
    float rotation = TransformGetRotation(transform);

    // Get a unit vector in the direction of the rotation.
    Vector2D direction;
    Vector2DFromAngleRad(&direction, rotation);

    // Get the current velocity of the spaceship.
    Vector2D velocity = *PhysicsGetVelocity(physics);

    // Calculate the new velocity (velocity = velocity + direction * spaceshipAcceleration * dt).
    Vector2DScaleAdd(&velocity, &velocity, (spaceshipAcceleration * dt), &direction);

    // Calculate the speed of the new velocity.
    float speed = Vector2DLength(&velocity);

    // If the speed exceeds the max speed, limit it.
    if (speed > spaceshipSpeedMax) {
        // Normalize the velocity and scale it to the maximum speed.
        Vector2DNormalize(&velocity, &velocity);
        Vector2DScale(&velocity, &velocity, spaceshipSpeedMax);
    }

    // Set the new velocity in the physics component.
    PhysicsGetVelocity(physics);
}

// Update the spaceship's weapon cooldown and fire a bullet if possible
static void BehaviorSpaceshipUpdateWeapon(Behavior* behavior, float dt)
{
    if (behavior->timer > 0.0f) {
        behavior->timer -= dt;
        if (behavior->timer < 0.0f) {
            behavior->timer = 0.0f;
        }
    }

    if (DGL_Input_KeyTriggered(VK_SPACE)) {
        if (behavior->timer <= 0.0f) {
            BehaviorSpaceshipSpawnBullet(behavior);
            behavior->timer = spaceshipWeaponCooldownTime;
        }
    }
}

// Spawn a bullet when the spaceship fires
static void BehaviorSpaceshipSpawnBullet(Behavior* behavior)
{
    Entity* parent = behavior->parent;
    if (!parent) return;

    Entity* bullet = EntityFactoryBuild("Bullet");
    if (!bullet) return;

    // Get position and rotation of the spaceship.
    Transform* transform = EntityGetTransform(parent);
    Vector2D position = *TransformGetTranslation(transform);
    float rotation = TransformGetRotation(transform);

    // Set bullet's position and rotation.
    Transform* bulletTransform = EntityGetTransform(bullet);
    TransformSetTranslation(bulletTransform, &position);
    TransformSetRotation(bulletTransform, rotation);

    // Get a unit vector in direction of the spaceship’s ‘rotation’.
    Vector2D direction;
    Vector2DFromAngleRad(&direction, rotation);

    // Set the bullet’s velocity = direction * spaceshipWeaponBulletSpeed.
    Physics* bulletPhysics = EntityGetPhysics(bullet);
    Vector2DScale(&direction, &direction, spaceshipWeaponBulletSpeed);
    PhysicsSetVelocity(bulletPhysics, &direction);

    // Add the cloned bullet to the Entity manager’s active list.
    EntityContainerAddEntity(bullet);
}
