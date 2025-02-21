//------------------------------------------------------------------------------
//
// File Name:	EntityContainer.h
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
extern "C" {	// Assume C declarations for C++.
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct Entity Entity;
typedef struct EntityContainer EntityContainer;

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Typedefs:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// An example of the structure to be defined in EntityContainer.c.
#if 0
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
	Entity*	entities[entityArraySize];

} EntityContainer;
#endif

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new EntityContainer.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (Hint: If your implementation requires any variables to be initialized to
//    non-zero values, then do so here.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
EntityContainer* EntityContainerCreate();

// Free the memory associated with an EntityContainer.
// (NOTE: If necessary, call EntityContainerFreeAll to free any existing Entities.)
// (NOTE: The EntityContainer pointer must be set to NULL.)
// Params:
//	 entities = Pointer to the EntityContainer pointer.
void EntityContainerFree(EntityContainer** entities);

// Add an Entity to the EntityContainer.
// (NOTE: If the container is not full, then the Entity should be added to the list
//    and the entityCount incremented by 1.)
// Params:
//   entities = Pointer to the EntityContainer.
// Returns:
//	 If the EntityContainer pointer is valid and the Entity was added successfully,
//		then return true,
//		else return false.
bool EntityContainerAddEntity(EntityContainer* entities, Entity* entity);

// Find an Entity in the EntityContainer that has a matching name.
// (HINT: Use the new function, EntityIsNamed, to compare names.)
// Params:
//   entities = Pointer to the EntityContainer.
//   entityName = The name of the Entity to be returned.
// Returns:
//	 If the EntityContainer pointer is valid and the Entity was located successfully,
//		then return a pointer to the Entity,
//		else return NULL.
Entity* EntityContainerFindByName(const EntityContainer* entities, const char* entityName);

// Determines if the EntityContainer is empty (no Entities exist).
// Params:
//   entities = Pointer to the EntityContainer.
// Returns:
//	 If the EntityContainer pointer is valid and no Entities exist,
//		then return true,
//		else return false.
bool EntityContainerIsEmpty(const EntityContainer* entities);

// Update all Entities in the EntityContainer.
// (HINT: You must call EntityUpdate for all Entities.)
// (NOTE: After an Entity has been updated, if it has been flagged as
//    destroyed, then it must be removed from the list and freed properly.
//    Additionally, the entityCount should be decremented by 1.)
// Params:
//   entities = Pointer to the EntityContainer.
//	 dt = Change in time (in seconds) since the last game loop.
void EntityContainerUpdateAll(EntityContainer* entities, float dt);

// Render all Entities in the EntityContainer.
// (HINT: You must call EntityRender for all Entities.)
// Params:
//   entities = Pointer to the EntityContainer.
void EntityContainerRenderAll(const EntityContainer* entities);

// Free all Entities in the EntityContainer.
// (NOTE: You must call EntityFree for all Entities.)
// (HINT: The container must be completely empty after this function is called.)
// (HINT: The entityCount should be 0 after all of the Entities have been freed.)
// Params:
//   entities = Pointer to the EntityContainer.
void EntityContainerFreeAll(EntityContainer* entities);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       // End of extern "C" {
#endif

