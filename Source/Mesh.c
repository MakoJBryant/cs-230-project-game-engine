//------------------------------------------------------------------------------
//
// File Name:	Mesh.c
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
#include "Mesh.h"
#include "DGL.h"
#include "Trace.h"
#include "Stream.h"
#include <Assert.h>

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

// Build a quadrilateral mesh and store it in the specified Mesh object.
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

// Build a "spaceship" mesh and store it in the specified Mesh object.
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

// Read the properties of a Mesh object from a file.
void MeshRead(Mesh* mesh, Stream stream)
{
	if (mesh == NULL || stream == NULL) {
		TraceMessage("Error: MeshRead received NULL argument(s).");
		return;
	}

	// (NOTE: First, read a token from the file and verify that it is "Mesh".)
	const char* token = StreamReadToken(stream);
	if (token == NULL || strcmp(token, "Mesh") != 0) {
		TraceMessage("Error: MeshRead failed to read 'Mesh' token.");
		return;
	}

	// (NOTE: Second, read a token and store it in the Mesh's name variable.)
	token = StreamReadToken(stream);
	if (token == NULL) {
		TraceMessage("Error: MeshRead failed to read mesh name.");
		return;
	}
	strcpy_s(mesh->name, _countof(mesh->name), token);

	// (NOTE: Third, read an integer indicating the number of vertices to be read.)
	int numVertices = StreamReadInt(stream);
	if (numVertices <= 0) {
		TraceMessage("Error: MeshRead received invalid vertex count.");
		return;
	}

	// (NOTE: For each vertex, read a Vector2D (position), a DGL_Color (color), and a Vector2D (UV).)
	for (int i = 0; i < numVertices; ++i) {

		DGL_Vec2 position;
		DGL_Color color;
		DGL_Vec2 uv;

		StreamReadVector2D(stream, &position);
		StreamReadColor(stream, &color);
		StreamReadVector2D(stream, &uv);

		// (HINT: Call DGL_Graphics_AddVertex() to add a single vertex to the mesh.)
		DGL_Graphics_AddVertex(&position, &color, &uv);
	}

	mesh->meshResource = DGL_Graphics_EndMesh();
}

// Determines if a Mesh has the specified name.
bool MeshIsNamed(const Mesh* mesh, const char* name)
{
	if (mesh == NULL || name == NULL) {
		TraceMessage("Error: MeshIsNamed received NULL argument(s).");
		return false;
	}

	// Perform a string comparison and return the result (match = true).
	return strcmp(mesh->name, name) == 0;
}


// Render a mesh.
void MeshRender(const Mesh* mesh)
{
	// Verify that arguments are valid.
	if (mesh == NULL) {
		TraceMessage("Error: MeshRender received NULL argument(s).");
		return;
	}

	DGL_Graphics_DrawMesh(mesh->meshResource, mesh->drawMode);
}

// Free the memory associated with a mesh.
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

