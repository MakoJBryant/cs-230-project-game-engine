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

#include "stdafx.h"
#include "Entity.h"

#include "Trace.h"
#include "Physics.h"
#include "Sprite.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Entity
{
	// The name of the entity.
	// A buffer is used to allow each entity to have a unique name.
	// The buffer is hardcoded to an arbitrary length that will be sufficient
	//	 for all CS230 assignments.  You may, instead, use dynamically-allocated
	//	 arrays for this purpose but the additional complexity is unnecessary
	//	 and it is your responsibility to ensure that the memory is successfully
	//	 allocated and deallocated in all possible situations.
	// [NOTE: When setting the name, use strcpy_s() to reduce the risk of
	//	 buffer overruns. Additionally, do NOT hardcode the number "32" when
	//	 calling this function!  Instead, use the _countof() macro to get the
	//	 size of the "name" array.]
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
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
Entity* EntityCreate(void)
{
	// Create memory for object.
	Entity* newEntity = (Entity*)calloc(1, sizeof(Entity));

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
// (NOTE: All attached components must be freed using the corresponding Free() functions.)
// (NOTE: The Entity pointer must be set to NULL.)
// Params:
//	 entity = Pointer to the Entity pointer.
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
// [NOTE: See project instructions for implementation instructions.]
// Params:
//	 entity = Pointer to the Entity.
//	 stream = The data stream used for reading.
void EntityRead(Entity* entity, Stream stream)
{
	UNREFERENCED_PARAMETER(entity);
	UNREFERENCED_PARAMETER(stream);
}

// Attach a Physics component to an Entity.
// Params:
//	 entity = Pointer to the Entity.
//   physics = Pointer to the Physics component to be attached.
void EntityAddPhysics(Entity* entity, Physics* physics)
{
	if (entity != NULL) {
		entity->physics = physics;
	}
}

// Attach a sprite component to an Entity.
// Params:
//	 entity = Pointer to the Entity.
//   sprite = Pointer to the Sprite component to be attached.
void EntityAddSprite(Entity* entity, Sprite* sprite)
{
	if (entity != NULL) {
		entity->sprite = sprite;
	}
}

// Attach a transform component to an Entity.
// Params:
//	 entity = Pointer to the Entity.
//   transform = Pointer to the Transform component to be attached.
void EntityAddTransform(Entity* entity, Transform* transform)
{
	if (entity != NULL) {
		entity->transform = transform;
	}
}

// Set the Entity's name.
// [NOTE: Verify that both pointers are valid before setting the name.]
// [NOTE: When setting the name, use strcpy_s() to reduce the risk of
//	 buffer overruns. Additionally, do NOT hardcode the number "32" when
//	 calling this function!  Instead, use the _countof() macro to get the
//	 size of the "name" array.]
// Params:
//	 entity = Pointer to the Entity.
//	 name = Pointer to the Entity's new name.
void EntitySetName(Entity* entity, const char* name)
{
	UNREFERENCED_PARAMETER(entity);
	UNREFERENCED_PARAMETER(name);
}

// Get the Entity's name.
// Params:
//	 entity = Pointer to the Entity.
// Returns:
//	 If the Entity pointer is valid,
//		then return a pointer to the Entity's name,
//		else return NULL.
const char* EntityGetName(const Entity* entity)
{
	UNREFERENCED_PARAMETER(entity);
}

// Get the Physics component attached to an Entity.
// Params:
//	 entity = Pointer to the Entity.
// Returns:
//	 If the Entity pointer is valid,
//		then return a pointer to the attached physics component,
//		else return NULL.
Physics* EntityGetPhysics(const Entity* entity)
{
	// ternary conditional operator
	return entity ? entity->physics : NULL;
}

// Get the Sprite component attached to a Entity.
// Params:
//	 entity = Pointer to the Entity.
// Returns:
//	 If the Entity pointer is valid,
//		then return a pointer to the attached Sprite component,
//		else return NULL.
Sprite* EntityGetSprite(const Entity* entity)
{
	// ternary conditional operator
	return entity ? entity->sprite : NULL;
}

// Get the Transform component attached to a Entity.
// Params:
//	 entity = Pointer to the Entity.
// Returns:
//	 If the Entity pointer is valid,
//		then return a pointer to the attached Transform component,
//		else return NULL.
Transform* EntityGetTransform(const Entity* entity)
{
	// ternary conditional operator
	return entity ? entity->transform : NULL;
}

// Update any components attached to the Entity.
// (Hint: You will need to call PhysicsUpdate().)
// (NOTE: You must first check for a valid pointer before calling this function.)
// Params:
//	 entity = Pointer to the Entity.
//	 dt = Change in time (in seconds) since the last game loop.
void EntityUpdate(Entity* entity, float dt)
{
	UNREFERENCED_PARAMETER(dt);
	UNREFERENCED_PARAMETER(entity);
}

// Render any visible components attached to the Entity.
// (Hint: You will need to call SpriteRender(), passing the Sprite and Transform components.)
// (NOTE: You must first check for valid pointers before calling this function.)
// Params:
//	 entity = Pointer to the Entity.
void EntityRender(Entity* entity)
{
	UNREFERENCED_PARAMETER(entity);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void TestEntityCreate() 
{
	Entity* entity = EntityCreate();

	// Check if entity is allocated.
	if (entity == NULL) {
		printf("Error: EntityCreate failed.\n");
		return;
	}
	printf("Entity created successfully.\n");
	
	// Check if components aren't NULL.
	if (entity->physics != 0 && entity->sprite != 0 && entity->transform != 0) {
		printf("Error: Some components of entity are not 0.\n");
	}
	printf("All components are NULL as expected.\n");

	// Free the entity after testing
	EntityFree(&entity);
	return;
}

static void TestEntityFree() 
{
	Entity* entity = EntityCreate();

	// Create mock components.
	Physics* physics = PhysicsCreate();
	Sprite* sprite = SpriteCreate();
	Transform* transform = TransformCreate();

	EntityAddPhysics(entity, physics);
	EntityAddSprite(entity, sprite);
	EntityAddTransform(entity, transform);

	// Free the entity
	EntityFree(&entity);

	// Check if the entity is NULL
	if (entity == NULL) {
		printf("Entity is freed and pointer is set to NULL.\n");
	} else {
		printf("Error: Entity is not NULL after freeing.\n");
	}
}

static void TestEntityAddAndGet() {
	// Create the entity.
	Entity* entity = EntityCreate();

	// Create mock components.
	Physics* physics = PhysicsCreate();
	Sprite* sprite = SpriteCreate();
	Transform* transform = TransformCreate();

	// Add components to the entity.
	EntityAddPhysics(entity, physics);
	EntityAddSprite(entity, sprite);
	EntityAddTransform(entity, transform);

	// Get components and check if they match.
	if (EntityGetPhysics(entity) == physics) {
		printf("Physics component correctly added and retrieved.\n");
	} else {
		printf("Error: Physics component mismatch.\n");
	}
	if (EntityGetSprite(entity) == sprite) {
		printf("Sprite component correctly added and retrieved.\n");
	} else {
		printf("Error: Sprite component mismatch.\n");
	}
	if (EntityGetTransform(entity) == transform) {
		printf("Transform component correctly added and retrieved.\n");
	} else {
		printf("Error: Transform component mismatch.\n");
	}

	// Free allocated components and the entity
	EntityFree(&entity);
}