//------------------------------------------------------------------------------
//
// File Name:	EntityFactory.c
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
#include "EntityFactory.h"
#include "Stream.h"
#include "Trace.h"

// Components.
#include "Entity.h" // EntityRead()
#include "EntityContainer.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static EntityContainer* archetypes = NULL;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Build a single instance of the specified Entity.
// (NOTE: Use sprintf_s() to construct a path name using objectName.)
// (HINT: The correct path name should be constructed using "Data/&s.txt".)
// (HINT: See project instructions.)
// Params:
//	 entityName = The name of the Entity to be constructed.
// Returns:
//	 If the objectName is not NULL,
//	   then return a pointer to a new instance of the specified Entity,
//	   else NULL.
Entity* EntityFactoryBuild(const char* entityName)
{
    if (entityName == NULL) {
        TraceMessage("Error: EntityFactoryBuild received NULL argument(s).");
        return NULL;
    }

    // Initialize archetypes container if it is NULL.
    if (archetypes == NULL) {
        archetypes = EntityContainerCreate();
        if (archetypes == NULL) {
            TraceMessage("Error: EntityFactoryBuild failed to create archetype container.");
            return NULL;
        }
    }

    // Check if the entity already exists in the archetypes container.
    Entity* existingEntity = EntityContainerFindByName(archetypes, entityName);
    if (existingEntity != NULL) {
        // Clone the archetype entity and return it.
        return EntityClone(existingEntity);
    }

    // Construct the file pathname.
    char pathName[FILENAME_MAX] = "";
    sprintf_s(pathName, _countof(pathName), "Data/%s.txt", entityName);

    // Open the data file for streaming.
    Stream fileStream = StreamOpen(pathName);
    if (fileStream == NULL) {
        TraceMessage("Error: EntityFactoryBuild failed to open stream for file %s.", pathName);
        return NULL;
    }

    // Read the first token from the file.
    const char* token = StreamReadToken(fileStream);

    // Verify that the first token is “Entity”.
    if (token == NULL || strncmp(token, "Entity", _countof("Entity") - 1) != 0) {
        TraceMessage("Error: EntityFactoryBuild failed to verify first token.");
        StreamClose(&fileStream);
        return NULL;
    }

    // Call EntityCreate to create a new archetype.
    Entity* newEntity = EntityCreate();
    if (newEntity == NULL) {
        TraceMessage("Error: EntityFactoryBuild failed to create new Entity.");
        StreamClose(&fileStream);
        return NULL;
    }

    // Call EntityRead() to populate the new entity.
    EntityRead(newEntity, fileStream);

    // Add the new entity to the archetypes container.
    EntityContainerAddEntity(archetypes, newEntity);

    // Close the file stream.
    StreamClose(&fileStream);

    // Clone and return the created archetype entity.
    return EntityClone(newEntity);
}

// Free all archetype Entities.
// (Hint: If the "archetypes" container exists, then the EntityContainerFreeAll
//    function must be called.)
void EntityFactoryFreeAll()
{
    if (archetypes == NULL) {
        TraceMessage("Warning: EntityFactoryFreeAll received NULL argument(s).");
    }
    EntityContainerFreeAll(archetypes);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
