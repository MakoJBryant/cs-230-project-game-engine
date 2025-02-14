//------------------------------------------------------------------------------
//
// File Name:	EntityFactory.c
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
#include "EntityFactory.h"
#include "Stream.h"
#include "Trace.h"

// Components.
#include "Entity.h" // EntityRead()

//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Build a single instance of the specified entity.
Entity* EntityFactoryBuild(const char* filename)
{
    if (filename == NULL) {
        TraceMessage("Error: EntityFactoryBuild received NULL argument(s).");
        return NULL;
    }

    // Open the file using StreamOpen().
    Stream fileStream = StreamOpen(filename);
    if (fileStream == NULL) {
        TraceMessage("Error: EntityFactoryBuild failed to open stream.");
        return NULL;
    }

    // Read the first token from the file using StreamReadToken().
    const char* token = StreamReadToken(fileStream);

    // Verify that the first token is “Entity” using strncmp().
    if (token == NULL || strncmp(token, "Entity", _countof("Entity") - 1) != 0) {
        TraceMessage("Error: EntityFactoryBuild failed to verify first token.");
        StreamClose(&fileStream);
        return NULL;
    }

    // Create a new entity using EntityCreate().
    Entity* newEntity = EntityCreate();
    if (newEntity == NULL) {
        TraceMessage("Error: EntityFactoryBuild failed to create new Entity.");
        StreamClose(&fileStream);
        return NULL;
    }

    // Call EntityRead(), passing the created Entity.
    EntityRead(newEntity, fileStream);

    // Close the file using StreamClose().
    StreamClose(&fileStream);

    // Return the created entity.
    return newEntity;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
