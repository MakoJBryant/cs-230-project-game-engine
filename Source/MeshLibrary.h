//------------------------------------------------------------------------------
//
// File Name:	MeshLibrary.h
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
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct Mesh Mesh;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// An example of the structure to be defined in MeshLibrary.c.
#if 0
// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef struct MeshLibrary
{
	// This variable is not required but could be used for tracking the number
	//   of Mesh objects currently in the list.
	unsigned int meshCount;

	// A list of all currently loaded meshes.
	// This list can be a fixed-length array (minimum size of 10 entries)
	// or a dynamically-sized array, such as a linked list.
	const Mesh* meshList[meshListSize];

} MeshLibrary;
#endif

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the Mesh Library.
// (NOTE: Make sure to initialize all memory to zero.)
void MeshLibraryInit();

// Build a mesh and add it to the mesh library, if it doesn't already exist.
//   1: Verify that a valid name was specified (not NULL).
//   2: Search for an existing mesh with a matching name.
//   3: If an existing mesh was NOT found, then create a new one from the data file:
//      a: Use sprintf_s() to construct a path name using meshName.
//	       (HINT: The correct path name should be constructed using "Data/%s.txt".)
//      b: Call StreamOpen(), passing the pathname.
//      c: If the stream was opened successfully,
//	       1: Call MeshCreate() to create an empty Mesh object.
//         2: Call MeshRead() to read the contents of the mesh from the file.
//	       3: Call MeshLibraryAdd(), passing the created mesh.
//	       4: Close the stream.
//   4: Return the mesh (either existed, created, or NULL).
// Params:
//	 meshName = The name of the mesh to be created.
// Returns:
//	 If the mesh already existed or was created successfully,
//	   then return a pointer to the mesh,
//	   else return NULL.
const Mesh* MeshLibraryBuild(const char * meshName);

// Free all Mesh objects in the Mesh Library.
// (NOTE: You must call MeshFree() to free each Mesh object.)
// (HINT: The list should contain nothing but NULL pointers once this function is done.)
void MeshLibraryFreeAll();

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

