//------------------------------------------------------------------------------
//
// File Name:	Mesh.c
// Author(s):	Mako J. Bryant (0068410)
// Project:		Project 2
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Mesh.h"
#include "DGL.h" // DGL_Mesh, DGL_DrawMode
#include "Trace.h" // TraceMessage()
#include <Assert.h> // assert()

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Mesh
{
	// The name of the Mesh.  This will be used later in the semester.
	char name[32];

	// Pointer to the DGL_Mesh resource.
	const DGL_Mesh* meshResource;

	// The draw mode to use when rendering the mesh (Usually "DGL_DM_TRIANGLELIST").
	DGL_DrawMode drawMode;
} Mesh;

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

// Dynamically allocate a new Mesh object but leave it empty.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/
// Returns:
//	 If the mesh was created successfully,
//	   then return a pointer to the created Mesh,
//	   else return NULL.
Mesh* MeshCreate()
{
	Mesh* newMesh = (Mesh*) calloc(1, sizeof(Mesh));

	if (newMesh == NULL) {
		TraceMessage("Graphics: MeshCreate() FAILED, newMesh is NULL.");
		return NULL;
	}

	return newMesh;
}

// Build a quadrilateral mesh and store it in the specified Mesh object.
// (NOTE: The DGL_Mesh object must be created using DGL_Graphics_StartMesh,
//    DGL_Graphics_AddTriangle, and DGL_Graphics_EndMesh.)
// (NOTE: The Mesh name can be stored using strcpy_s(). For example:
//    strcpy_s(mesh->name, _countof(mesh->name), name); )
// (NOTE: The drawMode should be set to DGL_DM_TRIANGLELIST.)
// Params:
//   mesh = Pointer to an existing, empty Mesh object.
//	 xHalfSize = The X half-size of the mesh.
//	 yHalfSize = The Y half-size of the mesh.
//   uSize = The U size of the mesh, relative to texture coordinates (0.0 .. 1.0).
//   vSize = The V size of the mesh, relative to texture coordinates (0.0 .. 1.0).
//	 name = A name for the mesh.
void MeshBuildQuad(Mesh* mesh, float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name)
{
	// Settings.
	mesh->drawMode = DGL_DM_TRIANGLELIST;
	strcpy_s(mesh->name, _countof(mesh->name), name);

	// Informing the library that we're about to start adding triangles.
	DGL_Graphics_StartMesh();

	// Each Vector: Position, Color, UV.
	DGL_Graphics_AddTriangle(
		&(DGL_Vec2){ -xHalfSize, -yHalfSize }, &(DGL_Color){ 1.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){  0.0f, vSize }, // red
		&(DGL_Vec2){  xHalfSize,  yHalfSize }, &(DGL_Color){ 0.0f, 1.0f, 0.0f, 1.0f }, &(DGL_Vec2){ uSize,  0.0f }, // green
		&(DGL_Vec2){  xHalfSize, -yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 1.0f, 1.0f }, &(DGL_Vec2){ uSize, vSize }); // blue
	DGL_Graphics_AddTriangle(
		&(DGL_Vec2){ -xHalfSize, -yHalfSize }, &(DGL_Color){ 1.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){  0.0f, vSize }, // red
		&(DGL_Vec2){ -xHalfSize,  yHalfSize }, &(DGL_Color){ 0.0f, 1.0f, 0.0f, 1.0f }, &(DGL_Vec2){  0.0f,  0.0f }, // green
		&(DGL_Vec2){  xHalfSize,  yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 1.0f, 1.0f }, &(DGL_Vec2){ uSize,  0.0f }); // blue

	// Save the mesh (list of triangles).
	mesh->meshResource = DGL_Graphics_EndMesh();
	assert(mesh && "Graphics: Failed to create mesh!");

}

// Build a "spaceship" mesh and store it in the specified Mesh object.
// (NOTE: This must be a "unit"-sized triangular mesh with the same characteristics as
//    the "triangular, colored mesh" created in DemoScene.c.)
// (NOTE: The DGL_Mesh object must be created using DGL_Graphics_StartMesh,
//    DGL_Graphics_AddTriangle, and DGL_Graphics_EndMesh.)
// (NOTE: The Mesh name can be stored using strcpy_s().)
// (NOTE: The drawMode should be set to DGL_DM_TRIANGLELIST.)
// Params:
//   mesh = Pointer to an existing, empty Mesh object.
void MeshBuildSpaceship(Mesh* mesh)
{
	UNREFERENCED_PARAMETER(mesh);
}

// Render a mesh.
// (NOTE: This is done using DGL_Graphics_DrawMesh().)
// Params:
//   mesh = Pointer to a Mesh to be rendered.
void MeshRender(const Mesh* mesh)
{
	UNREFERENCED_PARAMETER(mesh);
}

// Free the memory associated with a mesh.
// (NOTE: The DGL_Mesh resource must be freed using DGL_Graphics_FreeMesh().)
// (NOTE: The Mesh object must be freed using free().
// (NOTE: The Mesh pointer must be set to NULL.)
// Params:
//   mesh = Pointer to the Mesh pointer.
void MeshFree(Mesh** mesh)
{
	if (*mesh != NULL) {

		// Must dereference the (pointer to the pointer) before you can access the (pointer).
		DGL_Graphics_FreeMesh(&(*mesh)->meshResource);

		free(*mesh);
		*mesh = NULL;
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

