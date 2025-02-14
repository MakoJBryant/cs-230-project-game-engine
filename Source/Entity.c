//------------------------------------------------------------------------------
//
// File Name:	Entity.c
// Author(s):	Mako J. Bryant (0068410)
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

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Entity
{
	// The name of the entity.
	char name[32];

	// Pointer to an attached physics component.
	Physics* physics;

	// Pointer to an attached sprite component.
	Sprite* sprite;

	// Pointer to an attached transform component.
	Transform* transform;

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
	newEntity->physics = 0;
	newEntity->sprite = 0;
	newEntity->transform = 0;

	return newEntity;
}

// Free the memory associated with an Entity.
void EntityFree(Entity** entity)
{
	// Verify that arguments are valid.
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

	// Free the entity object and nullify dangling pointer.
	free(*entity);
	*entity = NULL;
}

// Read (and construct) the components associated with a entity.
void EntityRead(Entity* entity, Stream stream)
{
	// If the Entity and Stream pointers are not NULL.
	if (entity == NULL || stream == NULL) {
		TraceMessage("Error: EntityRead received NULL argument(s).");
	}

	// Read a token from the stream.
	const char* token = StreamReadToken(stream);
	if (token != NULL && token[0] != '\0') {
		// Use the token to set the Entity's name.
		EntitySetName(entity, token);
	} else {
		TraceMessage("Error: EntityRead failed to read token from stream.");
		return;
	}

	// While (true),
	while (true) {

		// Read a token from the stream.
		token = StreamReadToken(stream);
		if (token == NULL || token[0] == '\0') {
			break;
		}

		// If “token” contains “Transform”,
		if (strstr(token, "Transform") != NULL) {
			// 1) Create a new transform component using TransformCreate().
			Transform* newTransform = TransformCreate();
			if (newTransform != NULL) {
				// 2) Call TransformRead(), passing the created transform.
				TransformRead(newTransform, stream);
				// 3) Add the transform to the entity.
				EntityAddTransform(entity, newTransform);
			} else {
				TraceMessage("Error: EntityRead failed to create Transform component.");
			}
		}
		// Else if “token” contains “Physics”,
		else if (strstr(token, "Physics") != NULL) {
			// Repeat steps 1-3 above, replacing “Transform” with “Physics”.
			Physics* newPhysics = PhysicsCreate();
			if (newPhysics != NULL) {
				PhysicsRead(newPhysics, stream);
				EntityAddPhysics(entity, newPhysics);
			} else {
				TraceMessage("Error: EntityRead failed to create Physics component.");
			}
		}
		// Else if “token” contains “Sprite”,
		else if (strstr(token, "Sprite") != NULL) {
			// Repeat steps 1-3 above, replacing “Transform” with “Sprite”.
			Sprite* newSprite = SpriteCreate();
			if (newSprite != NULL) {
				SpriteRead(newSprite, stream);
				EntityAddSprite(entity, newSprite);
			} else {
				TraceMessage("Error: EntityRead failed to create Sprite component.");
			}
		}
		// Else if “token” is empty (zero-length string), break out of the loop.
		else if (token[0] == '\0') {
			break;
		}
		// Else log a warning for unrecognized token(s).
		else {
			TraceMessage("Warning: EntityRead has unrecognized token '%s' in stream.", token);
			break;
		}
	}
}

// Attach an Animation component to an Entity.
// (NOTE: This function must set the animation component's parent pointer by
//	  calling the AnimationSetParent() function.)
// Params:
//	 entity = Pointer to the Entity.
//   animation = Pointer to the Animation component to be attached.
void EntityAddAnimation(Entity* entity, Animation* animation)
{
	UNREFERENCED_PARAMETER(entity);
	UNREFERENCED_PARAMETER(animation);
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
	// ternary conditional operator
	return entity ? entity->name : NULL;
}

// Get the Animation component attached to an Entity.
// Params:
//	 entity = Pointer to the Entity.
// Returns:
//	 If the Entity pointer is valid,
//		then return a pointer to the attached Animation component,
//		else return NULL.
Animation* EntityGetAnimation(const Entity* entity)
{
	UNREFERENCED_PARAMETER(entity);
	return NULL;
}

// Get the Physics component attached to an Entity.
Physics* EntityGetPhysics(const Entity* entity)
{
	// ternary conditional operator
	return entity ? entity->physics : NULL;
}

// Get the Sprite component attached to a Entity.
Sprite* EntityGetSprite(const Entity* entity)
{
	// ternary conditional operator
	return entity ? entity->sprite : NULL;
}

// Get the Transform component attached to a Entity.
Transform* EntityGetTransform(const Entity* entity)
{
	// ternary conditional operator
	return entity ? entity->transform : NULL;
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
