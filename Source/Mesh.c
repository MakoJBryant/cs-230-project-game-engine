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

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

// Essentials.
#include "stdafx.h"
#include "Mesh.h"
#include "DGL.h"
#include "Trace.h"
#include <Assert.h>

//------------------------------------------------------------------------------

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

Mesh* MeshCreate()
{
	// Allocate memory for new Mesh object.
	Mesh* newMesh = calloc(1, sizeof(Mesh));

	// Verify that memory allocation was successful.
	if (newMesh == NULL) {
		TraceMessage("Error: MeshCreate failed to allocate memory.");
		return NULL;
	}

	return newMesh;
}

void MeshBuildQuad(Mesh* mesh, float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name)
{
	// Verify that arguments are valid.
	if (mesh == NULL || name == NULL) {
		TraceMessage("Error: MeshBuildQuad received NULL argument(s).");
		return;
	}

	// Settings.
	mesh->drawMode = DGL_DM_TRIANGLELIST;
	strcpy_s(mesh->name, _countof(mesh->name), name);
	static const DGL_Color DGL_Color_None = { 0.0f, 0.0f, 0.0f, 1.0f };

	// Informing the library that we're about to start adding triangles.
	DGL_Graphics_StartMesh();

	// Each Vector: Position, Color, UV.
	DGL_Graphics_AddTriangle(
		&(DGL_Vec2){ -xHalfSize, -yHalfSize }, &DGL_Color_None, &(DGL_Vec2){  0.0f, vSize },
		&(DGL_Vec2){  xHalfSize,  yHalfSize }, &DGL_Color_None, &(DGL_Vec2){ uSize,  0.0f },
		&(DGL_Vec2){  xHalfSize, -yHalfSize }, &DGL_Color_None, &(DGL_Vec2){ uSize, vSize });
	DGL_Graphics_AddTriangle(
		&(DGL_Vec2){ -xHalfSize, -yHalfSize }, &DGL_Color_None, &(DGL_Vec2){  0.0f, vSize },
		&(DGL_Vec2){ -xHalfSize,  yHalfSize }, &DGL_Color_None, &(DGL_Vec2){  0.0f,  0.0f },
		&(DGL_Vec2){  xHalfSize,  yHalfSize }, &DGL_Color_None, &(DGL_Vec2){ uSize,  0.0f });

	// Save the mesh (list of triangles).
	mesh->meshResource = DGL_Graphics_EndMesh();
	assert(mesh && "MeshBuildQuad: failed to create mesh!");

}

void MeshBuildSpaceship(Mesh* mesh)
{
	// Verify that arguments are valid.
	if (mesh == NULL) {
		TraceMessage("Error: MeshBuildSpaceship received NULL argument(s).");
		return;
	}

	// Settings.
	mesh->drawMode = DGL_DM_TRIANGLELIST;
	strcpy_s(mesh->name, _countof(mesh->name), "Spaceship");
	static const DGL_Color DGL_Color_Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
	static const DGL_Color DGL_Color_Red = { 1.0f, 0.0f, 0.0f, 1.0f };

	// Create a triangular, colored mesh.
	DGL_Graphics_StartMesh();
	DGL_Graphics_AddTriangle(
		&(DGL_Vec2){  0.5f,  0.0f }, &DGL_Color_Yellow, &(DGL_Vec2){ 0.0f, 0.0f },
		&(DGL_Vec2){ -0.5f, -0.5f }, &DGL_Color_Red, &(DGL_Vec2){ 0.0f, 0.0f },
		&(DGL_Vec2){ -0.5f,  0.5f }, &DGL_Color_Red, &(DGL_Vec2){ 0.0f, 0.0f });

	// Save the mesh (list of triangles).
	mesh->meshResource = DGL_Graphics_EndMesh();
	assert(mesh && "MeshBuildSpaceship: failed to create mesh!");

}

void MeshRender(const Mesh* mesh)
{
	// Verify that arguments are valid.
	if (mesh == NULL) {
		TraceMessage("Error: MeshRender received NULL argument(s).");
		return;
	}

	DGL_Graphics_DrawMesh(mesh->meshResource, mesh->drawMode);
}

void MeshFree(Mesh** mesh)
{
	// Verify that arguments are valid.
	if (mesh == NULL || *mesh == NULL) {
		TraceMessage("Error: MeshFree received NULL argument(s).");
		return;
	}

	// Must dereference the (pointer to the pointer) before you can access the (pointer).
	DGL_Graphics_FreeMesh(&(*mesh)->meshResource);

	// Free the mesh and nullify the dangling pointer.
	free(*mesh);
	*mesh = NULL;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

