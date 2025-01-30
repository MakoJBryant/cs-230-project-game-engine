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

#include "stdafx.h"

#include "EntityFactory.h"
#include "Stream.h"
#include "Entity.h" // EntityRead()

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
// (HINT: See project instructions.)
// Params:
//	 filename = The name of the file to be deserialized.
// Returns:
//	 If the filename is valid
//	   then return a pointer to a new instance of the specified entity,
//	   else NULL.
Entity* EntityFactoryBuild(const char* filename)
{
    if (filename == NULL) {
        return NULL;
    }

    // Open the file using StreamOpen().
    Stream fileStream = StreamOpen(filename);
    if (fileStream == NULL) {
        return NULL;
    }

    // Read the first token from the file using StreamReadToken().
    const char* token = StreamReadToken(fileStream);

    // Verify that the first token is “Entity” using strncmp().
    if (token == NULL || strncmp(token, "Entity", _countof("Entity") - 1) != 0) {
        StreamClose(&fileStream);
        return NULL;
    }

    // Create a new entity using EntityCreate().
    Entity* newEntity = EntityCreate();
    if (newEntity == NULL) {
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

