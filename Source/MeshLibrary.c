//------------------------------------------------------------------------------
//
// File Name:	MeshLibrary.c
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
#include "MeshLibrary.h"
#include "Trace.h"
#include "Stream.h"

// Components.
#include "Mesh.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

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
	// TODO: Create dynamically sized array to replace this hard coded value.
	const Mesh* meshList[10]; // meshListSize

} MeshLibrary;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
static MeshLibrary meshes;

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
static void MeshLibraryAdd(const Mesh* mesh);
static const Mesh* MeshLibraryFind(const char* meshName);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the Mesh Library.
void MeshLibraryInit()
{
	// https://www.geeksforgeeks.org/memset-c-example/
	memset(&meshes, 0, sizeof(MeshLibrary));
}

// Build a mesh and add it to the mesh library, if it doesn't already exist.
const Mesh* MeshLibraryBuild(const char* meshName)
{
	if (!meshName) {
		TraceMessage("Error: MeshLibraryBuild received NULL argument.");
		return NULL;
	}

	const Mesh* existingMesh = MeshLibraryFind(meshName);
	if (existingMesh) {
		return existingMesh;
	}

	char filePath[64];
	sprintf_s(filePath, sizeof(filePath), "Data/%s.txt", meshName);

	Stream stream = StreamOpen(filePath);
	if (!stream) {
		TraceMessage("Error: MeshLibraryBuild failed to open file: %s.", filePath);
		return NULL;
	}

	Mesh* newMesh = MeshCreate();
	if (!newMesh) {
		StreamClose(&stream);
		return NULL;
	}

	MeshRead(newMesh, stream);
	MeshLibraryAdd(newMesh);
	StreamClose(&stream);

	return newMesh;
}

// Free all Mesh objects in the Mesh Library.
void MeshLibraryFreeAll()
{
	for (unsigned int i = 0; i < meshes.meshCount; ++i) {
		if (meshes.meshList[i]) {
			MeshFree(&meshes.meshList[i]);
		}
	}
	memset(&meshes, 0, sizeof(MeshLibrary));
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Find a mesh by name in the mesh library.
static const Mesh* MeshLibraryFind(const char* meshName)
{
	for (unsigned int i = 0; i < meshes.meshCount; ++i) {
		if (MeshIsNamed(meshes.meshList[i], meshName)) {
			return meshes.meshList[i];
		}
	}
	return NULL;
}

// Add a mesh to the mesh library.
static void MeshLibraryAdd(const Mesh* mesh)
{
	if (meshes.meshCount < 10) {
		meshes.meshList[meshes.meshCount++] = (Mesh*)mesh;
	}
	else {
		TraceMessage("Warning: MeshLibrary is full. Consider expanding capacity.");
	}
}
