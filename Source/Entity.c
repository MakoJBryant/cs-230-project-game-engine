//------------------------------------------------------------------------------
//
// File Name:	Entity.c
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
#include "Entity.h"
#include "Trace.h"
#include "Stream.h"

// Components.
#include "Physics.h"
#include "Sprite.h"
#include "Transform.h"
#include "Animation.h"
#include "Behavior.h"
#include "BehaviorSpaceship.h"
#include "BehaviorBullet.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Entity
{
	char name[32];				// The name of the entity.
	bool isDestroyed;			// Flag to indicate if the entity is destroyed.

	Physics* physics;			// Pointer to an attached physics component.
	Sprite* sprite;				// Pointer to an attached sprite component.
	Transform* transform;		// Pointer to an attached transform component.
	Animation* animation;		// Pointer to an attached animation component.
	Behavior* behavior;			// Pointer to an attached behavior component.

} Entity;

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

// Dynamically allocate a new Entity.
Entity* EntityCreate(void)
{
	// Create memory for object.
	Entity* newEntity = calloc(1, sizeof(Entity));

	// Verify that memory was allocated successfully.
	if (newEntity == NULL) {
		TraceMessage("Error: EntityCreate failed to allocated memory.");
		return NULL;
	}

	// Set default values.
	strcpy_s(newEntity->name, _countof(newEntity->name), "");
	newEntity->isDestroyed = false;

	newEntity->physics = NULL;
	newEntity->sprite = NULL;
	newEntity->transform = NULL;
	newEntity->behavior = NULL;

	return newEntity;
}

// Dynamically allocate a clone of an existing Entity.
Entity* EntityClone(const Entity* other)
{
	if (other == NULL) {
		TraceMessage("Error: EntityClone received NULL argument(s).");
		return NULL;
	}

	// Allocate memory for the new entity.
	Entity* newEntity = EntityCreate();
	if (newEntity == NULL) {
		TraceMessage("Error: EntityClone failed to allocate memory.");
		return NULL;
	}

	// Shallow copy of the data.
	strcpy_s(newEntity->name, _countof(newEntity->name), other->name);
	newEntity->isDestroyed = other->isDestroyed;

	// Deep copy of any attached components.
	if (other->transform != NULL) {
		Transform* newTransform = TransformClone(other->transform);
		if (newTransform != NULL) {
			EntityAddTransform(newEntity, newTransform);
		}
	}

	if (other->physics != NULL) {
		Physics* newPhysics = PhysicsClone(other->physics);
		if (newPhysics != NULL) {
			EntityAddPhysics(newEntity, newPhysics);
		}
	}

	if (other->sprite != NULL) {
		Sprite* newSprite = SpriteClone(other->sprite);
		if (newSprite != NULL) {
			EntityAddSprite(newEntity, newSprite);
		}
	}

	if (other->animation != NULL) {
		Animation* newAnimation = AnimationClone(other->animation);
		if (newAnimation != NULL) {
			EntityAddAnimation(newEntity, newAnimation);
		}
	}

	if (other->behavior != NULL) {
		Behavior* newBehavior = BehaviorClone(other->behavior);
		if (newBehavior != NULL) {
			EntityAddBehavior(newEntity, newBehavior);
		}
	}

	return newEntity;
}

// Free the memory associated with an Entity.
void EntityFree(Entity** entity)
{
	if (entity == NULL || *entity == NULL) {
		TraceMessage("Error: EntityFree received NULL argument(s).");
		return;
	}

	// Free the attached components, if they exist.
	if ((*entity)->physics != NULL) {
		PhysicsFree(&(*entity)->physics);
	}
	if ((*entity)->sprite != NULL) {
		SpriteFree(&(*entity)->sprite);
	}
	if ((*entity)->transform != NULL) {
		TransformFree(&(*entity)->transform);
	}
	if ((*entity)->animation != NULL) {
		AnimationFree(&(*entity)->animation);
	}
	if ((*entity)->behavior != NULL) {
		BehaviorFree(&(*entity)->behavior);
	}

	free(*entity);
	*entity = NULL;
}

// Read (and construct) the components associated with an entity.
void EntityRead(Entity* entity, Stream stream)
{
	if (entity == NULL || stream == NULL) {
		TraceMessage("Error: EntityRead received NULL argument(s).");
		return;
	}

	// Read a token from the stream.
	const char* token = StreamReadToken(stream);
	if (token != NULL && token[0] != '\0') {
		EntitySetName(entity, token);
	}
	else {
		TraceMessage("Error: EntityRead failed to read token from stream.");
		return;
	}

	while (true) {
		token = StreamReadToken(stream);
		if (token == NULL || token[0] == '\0') {
			break;
		}

		if (strstr(token, "Transform") != NULL) {
			Transform* newTransform = TransformCreate();
			if (newTransform != NULL) {
				TransformRead(newTransform, stream);
				EntityAddTransform(entity, newTransform);
			}
			else {
				TraceMessage("Error: EntityRead failed to create Transform component.");
			}
		}
		else if (strstr(token, "Physics") != NULL) {
			Physics* newPhysics = PhysicsCreate();
			if (newPhysics != NULL) {
				PhysicsRead(newPhysics, stream);
				EntityAddPhysics(entity, newPhysics);
			}
			else {
				TraceMessage("Error: EntityRead failed to create Physics component.");
			}
		}
		else if (strstr(token, "Sprite") != NULL) {
			Sprite* newSprite = SpriteCreate();
			if (newSprite != NULL) {
				SpriteRead(newSprite, stream);
				EntityAddSprite(entity, newSprite);
			}
			else {
				TraceMessage("Error: EntityRead failed to create Sprite component.");
			}
		}
		else if (strstr(token, "Animation") != NULL) {
			Animation* newAnimation = AnimationCreate();
			if (newAnimation != NULL) {
				AnimationRead(newAnimation, stream);
				EntityAddAnimation(entity, newAnimation);
			}
			else {
				TraceMessage("Error: EntityRead failed to create Animation component.");
			}
		}
		else if (strstr(token, "BehaviorSpaceship") != NULL) {
			Behavior* newBehavior = BehaviorSpaceshipCreate();
			if (newBehavior != NULL) {
				BehaviorRead(newBehavior, stream);
				EntityAddBehavior(entity, newBehavior);
			}
			else {
				TraceMessage("Error: EntityRead failed to create BehaviorSpaceship.");
			}
		}
		else if (strstr(token, "BehaviorBullet") != NULL) {
			Behavior* newBehavior = BehaviorBulletCreate();
			if (newBehavior != NULL) {
				BehaviorRead(newBehavior, stream);
				EntityAddBehavior(entity, newBehavior);
			}
			else {
				TraceMessage("Error: EntityRead failed to create BehaviorBullet.");
			}
		}
		else if (token[0] == '\0') {
			break;
		}
		else {
			TraceMessage("Warning: EntityRead has unrecognized token '%s' in stream.", token);
			break;
		}
	}
}

// Flag an Entity for destruction.
void EntityDestroy(Entity* entity)
{
	if (entity == NULL) {
		TraceMessage("Error: EntityDestroy received NULL argument(s).");
		return;
	}

	entity->isDestroyed = true;
}

// Check whether an Entity has been flagged for destruction.
bool EntityIsDestroyed(const Entity* entity)
{
	if (entity == NULL) {
		TraceMessage("Error: EntityIsDestroyed received NULL argument(s).");
		return false;
	}

	return entity->isDestroyed;
}

// Attach an Animation component to an Entity.
void EntityAddAnimation(Entity* entity, Animation* animation)
{
	if (entity != NULL && animation != NULL) {
		AnimationSetParent(animation, entity);
		entity->animation = animation;
	}
}

// Attach a Behavior component to an Entity.
void EntityAddBehavior(Entity* entity, Behavior* behavior)
{
	if (entity == NULL || behavior == NULL) {
		TraceMessage("Error: EntityAddBehavior received NULL argument(s).");
		return;
	}

	// Set the behavior's parent to the current entity
	BehaviorSetParent(behavior, entity);

	// Assign the behavior to the entity
	entity->behavior = behavior;
}

// Attach a Physics component to an Entity.
void EntityAddPhysics(Entity* entity, Physics* physics)
{
	if (entity != NULL) {
		entity->physics = physics;
	}
}

// Attach a sprite component to an Entity.
void EntityAddSprite(Entity* entity, Sprite* sprite)
{
	if (entity != NULL) {
		entity->sprite = sprite;
	}
}

// Attach a transform component to an Entity.
void EntityAddTransform(Entity* entity, Transform* transform)
{
	if (entity != NULL) {
		entity->transform = transform;
	}
}

// Set the Entity's name.
void EntitySetName(Entity* entity, const char* name)
{
	if (entity == NULL || name == NULL) {
		TraceMessage("Error: EntitySetName received NULL argument(s).");
		return;
	}

	strcpy_s(entity->name, _countof(entity->name), name);
}

// Get the Entity's name.
const char* EntityGetName(const Entity* entity)
{
	return entity ? entity->name : NULL;
}

// Compare the Entity's name with the specified name.
bool EntityIsNamed(const Entity* entity, const char* name)
{
	if (entity == NULL || name == NULL) {
		TraceMessage("Error: EntityIsNamed received NULL argument(s).");
		return false;
	}

	// Returns true if they match (strcmp() == 0).
	return strcmp(entity->name, name) == 0;
}

// Get the Animation component attached to an Entity.
Animation* EntityGetAnimation(const Entity* entity)
{
	return entity ? entity->animation : NULL;
}

// Get the Behavior component attached to an Entity.
Behavior* EntityGetBehavior(const Entity* entity)
{
	if (entity == NULL) {
		TraceMessage("Error: EntityGetBehavior received NULL argument(s).");
		return NULL;
	}

	return entity->behavior;
}

// Get the Physics component attached to an Entity.
Physics* EntityGetPhysics(const Entity* entity)
{
	if (entity == NULL) {
		TraceMessage("Error: EntityGetPhysics received NULL argument(s).");
		return NULL;
	}

	return entity->physics;
}

// Get the Sprite component attached to a Entity.
Sprite* EntityGetSprite(const Entity* entity)
{
	if (entity == NULL) {
		TraceMessage("Error: EntityGetSprite received NULL argument(s).");
		return NULL;
	}

	return entity->sprite;
}

// Get the Transform component attached to a Entity.
Transform* EntityGetTransform(const Entity* entity)
{
	if (entity == NULL) {
		TraceMessage("Error: EntityGetTransform received NULL argument(s).");
		return NULL;
	}

	return entity->transform;
}

// Update any components attached to the Entity.
void EntityUpdate(Entity* entity, float dt)
{
	if (entity == NULL) {
		TraceMessage("Error: EntityUpdate received NULL argument(s).");
		return;
	}

	// Update the entity's physics component if not NULL.
	if (entity->physics != NULL && entity->transform != NULL) {
		PhysicsUpdate(entity->physics, entity->transform, dt);
	}

	// Update the entity's animation component if not NULL.
	if (entity->animation != NULL) {
		AnimationUpdate(entity->animation, dt);
	}

	// Update the entity's behavior if not NULL.
	if (entity->behavior != NULL) {
		BehaviorUpdate(entity->behavior, dt);
	}
}

// Render any visible components attached to the Entity.
void EntityRender(Entity* entity)
{
	if (entity == NULL) {
		TraceMessage("Error: EntityRender received NULL argument(s).");
		return;
	}

	// Render the entity's sprite if not NULL.
	if (entity->sprite != NULL && entity->transform != NULL) {
		SpriteRender(entity->sprite, entity->transform);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
