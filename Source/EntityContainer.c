//------------------------------------------------------------------------------
//
// File Name:	EntityContainer.c
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
#include "EntityContainer.h"
#include "Trace.h"

// Components.
#include "Entity.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef struct EntityContainer
{
	// This variable is not required but could be used for tracking the number
	//   of Entities currently in the list.  Instructions on how to do this
	//   are included in the function headers.
	unsigned entityCount;

	// This variable is not required but could be used for different purposes.
	// - For storing the maximum size of the container.
	// - For tracking peak usage of the container, used for testing purposes.
	unsigned entityMax;

	// This list can be a fixed-length array (minimum size of 100 entries)
	// or a dynamically sized array, such as a linked list.
	// (NOTE: The implementation details are left up to the student.  However,
	//    it is your responsiblity to ensure that memory is handled correctly.)
	// TODO: Create dynamically sized array to replace this hard coded value.
	Entity* entities[100]; // entityArraySize

} EntityContainer;

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

// Dynamically allocate a new EntityContainer.
EntityContainer* EntityContainerCreate()
{
	// Allocate memory for the container and initialize to zero
	EntityContainer* container = calloc(1, sizeof(EntityContainer));
	if (container == NULL) {
		TraceMessage("Error: Failed to allocate memory for EntityContainer.");
		return NULL;
	}

	// Set initial values.
	container->entityCount = 0;
	container->entityMax = 100;

	// Initialize entity list to NULL
	for (unsigned i = 0; i < container->entityMax; i++) {
		container->entities[i] = NULL;
	}

	return container;
}

// Free the memory associated with an EntityContainer.
void EntityContainerFree(EntityContainer** entities)
{
	if (entities == NULL || *entities == NULL) {
		TraceMessage("Warning: Attempted to free a NULL EntityContainer.");
		return;
	}

	// Free all entities in the container.
	EntityContainerFreeAll(*entities);

	// Free the container itself.
	free(*entities);
	*entities = NULL; // Prevent dangling pointer.

	TraceMessage("EntityContainer successfully freed.");
}

// Add an Entity to the EntityContainer.
bool EntityContainerAddEntity(EntityContainer* entities, Entity* entity)
{
	if (entities == NULL || entity == NULL) {
		TraceMessage("Error: EntityContainerAddEntity recieved NULL argument(s).");
		return false;
	}

	if (entities->entityCount >= 100) {
		TraceMessage("Error: EntityContainer is full. Cannot add more entities.");
		return false;
	}

	// Loop to find the first available slot.
	for (unsigned i = 0; i < 100; i++) {
		// If empty slot is found,
		if (entities->entities[i] == NULL) {
			entities->entities[i] = entity;
			entities->entityCount++;
			TraceMessage("Entity successfully added to EntityContainer.");
			return true;
		}
	}

	TraceMessage("Error: Unable to find an available slot in EntityContainer.");
	return false;
}

// Find an Entity in the EntityContainer that has a matching name.
Entity* EntityContainerFindByName(const EntityContainer* entities, const char* entityName)
{
	if (entities == NULL || entityName == NULL) {
		TraceMessage("Error: EntityContainerFindByName received NULL argument(s).");
		return NULL;
	}

	// Loop through the entire list of entities.
	for (unsigned i = 0; i < 100; i++)
	{
		// If current Entity not NULL and name matches.
		if (entities->entities[i] != NULL 
			&& EntityIsNamed(entities->entities[i], entityName)) {
			
			TraceMessage("Entity found in EntityContainer.");
			return entities->entities[i];
		}
	}

	// Entity not found
	TraceMessage("Warning: Entity not found in EntityContainer.");
	return NULL;
}

// Determines if the EntityContainer is empty (no Entities exist).
bool EntityContainerIsEmpty(const EntityContainer* entities)
{
	if (entities == NULL) {
		TraceMessage("Error: EntityContainerIsEmpty received NULL argument(s).");
		return false;
	}

	// Loop through the entire list of entities.
	for (unsigned i = 0; i < 100; i++) {
		// If Entity is found, the container is not empty.
		if (entities->entities[i] != NULL) {
			return false;
		}
	}

	// No Entities found.
	return true;
}

// Update all Entities in the EntityContainer.
void EntityContainerUpdateAll(EntityContainer* entities, float dt)
{
	if (entities == NULL) {
		TraceMessage("Error: EntityContainerUpdateAll received NULL argument(s).");
		return;
	}

	// Iterate through all the entities in the container.
	for (unsigned i = 0; i < 100; i++) {
		if (entities->entities[i] != NULL) {

			EntityUpdate(entities->entities[i], dt);

			if (EntityIsDestroyed(entities->entities[i])) {

				// Destroy and free the Entity.
				EntityFree(&entities->entities[i]);
				entities->entities[i] = NULL;
				entities->entityCount--;
			}
		}
	}
}

// Render all Entities in the EntityContainer.
void EntityContainerRenderAll(const EntityContainer* entities)
{
	if (entities == NULL) {
		TraceMessage("Error: EntityContainerRenderAll received NULL argument(s).");
		return;
	}

	// Iterate through all the entities in the container.
	for (unsigned i = 0; i < 100; i++) {
		if (entities->entities[i] != NULL) {
			// Render the entity.
			EntityRender(entities->entities[i]);
		}
	}
}

// Free all Entities in the EntityContainer.
void EntityContainerFreeAll(EntityContainer* entities)
{
	if (entities == NULL) {
		TraceMessage("Error: EntityContainerFreeAll received NULL argument(s).");
		return;
	}

	// Iterate through all the entities in the container.
	for (unsigned i = 0; i < 100; i++) {
		if (entities->entities[i] != NULL) {
			// Free the entity.
			EntityFree(&entities->entities[i]);

			// Set the slot to NULL after freeing.
			entities->entities[i] = NULL;
		}
	}

	entities->entityCount = 0;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

