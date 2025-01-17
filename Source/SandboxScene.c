//------------------------------------------------------------------------------
//
// File Name:	SandboxScene.c
// Author(s):	Mako J. Bryant (0068410)
// Project:		Project 1
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Scene.h"
#include "SceneSystem.h"
#include "SandboxScene.h"
#include "Vector2D.h"
#include "Stream.h"
#include "Trace.h"


//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
static const char* traceFileName = "Data/VectorTests.txt";

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct SandboxScene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.

} SandboxScene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static FILE* traceFile;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void SandboxSceneLoad(void);
static void SandboxSceneInit(void);
static void SandboxSceneUpdate(float dt);
static void SandboxSceneExit(void);
static void SandboxSceneUnload(void);
static void SandboxSceneRender(void);

/*
static void SandboxSceneTraceFloat(const char* text, float f);
static void SandboxSceneTraceVector(const char* text, const Vector2D* v);
*/

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static SandboxScene instance =
{
	// Initialize the base structure:
	{ "Sandbox", SandboxSceneLoad, SandboxSceneInit, SandboxSceneUpdate, SandboxSceneRender, SandboxSceneExit, SandboxSceneUnload },

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Stub Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* SandboxSceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void SandboxSceneLoad(void)
{
}

// Initialize the entities and variables used by the scene.
static void SandboxSceneInit()
{
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void SandboxSceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);

	Stream file = StreamOpen(traceFileName);

	// If the stream was opened successfully.
	if (file != NULL) {

		// Create a single Vector2D variable for tests
		Vector2D v = { 4.0f, 3.0f };
		Vector2DZero(&v);
		TraceMessage("Vector Test: Vector2DZero = [%f, %f]", v.x, v.y);
		Vector2DSet(&v, 1.5f, 1.0f);
		TraceMessage("Vector Test: Vector2DSet = [%f, %f]", v.x, v.y);
		Vector2DNeg(&v, &v);
		TraceMessage("Vector Test: Vector2DNeg = [%f, %f]", v.x, v.y);
		Vector2DAdd(&v, &v, &v);
		TraceMessage("Vector Test: Vector2DAdd = [%f, %f]", v.x, v.y);
		Vector2DSub(&v, &v, &v);
		TraceMessage("Vector Test: Vector2DSub = [%f, %f]", v.x, v.y);
		StreamReadVector2D(file, &v);
		TraceMessage("Vector Test: StreamReadVector2D = [%f, %f]", v.x, v.y);
		Vector2DNormalize(&v, &v);
		TraceMessage("Vector Test: Vector2DNormalize = [%f, %f]", v.x, v.y);
		float scale = StreamReadFloat(file);
		TraceMessage("Vector Test: StreamReadFloat = %f", scale);
		Vector2DScale(&v, &v, scale);
		TraceMessage("Vector Test: Vector2DScale = [%f, %f]", v.x, v.y);
		Vector2DScaleAdd(&v, &v, scale, &v);
		TraceMessage("Vector Test: Vector2DScaleAdd = [%f, %f]", v.x, v.y);
		Vector2DScaleSub(&v, &v, scale, &v);
		TraceMessage("Vector Test: Vector2DScaleSub = [%f, %f]", v.x, v.y);
		TraceMessage("Vector Test: Vector2DLength = %f", Vector2DLength(&v));
		TraceMessage("Vector Test: Vector2DSquareLength = %f", Vector2DSquareLength(&v));

		Vector2D v2 = { 3.0f, 4.0f };
		StreamReadVector2D(file, &v);
		TraceMessage("Vector Test: StreamReadVector2D = [%f, %f]", v.x, v.y);
		StreamReadVector2D(file, &v2);
		TraceMessage("Vector Test: StreamReadVector2D = [%f, %f]", v2.x, v2.y);
		TraceMessage("Vector Test: Vector2DDistance = %f", Vector2DDistance(&v, &v2));
		TraceMessage("Vector Test: Vector2DSquareDistance = %f", Vector2DSquareDistance(&v, &v2));
		TraceMessage("Vector Test: Vector2DDotProduct = %f", Vector2DDotProduct(&v, &v2));

		float angle = StreamReadFloat(file);
		TraceMessage("Vector Test: StreamReadFloat = %f", angle);
		Vector2DFromAngleDeg(&v, angle);
		TraceMessage("Vector Test: Vector2DFromAngleDeg = [%f, %f]", v.x, v.y);
		angle = StreamReadFloat(file);
		TraceMessage("Vector Test: StreamReadFloat = %f", angle);
		Vector2DFromAngleRad(&v, angle);
		TraceMessage("Vector Test: Vector2DFromAngleRad = [%f, %f]", v.x, v.y);
		TraceMessage("Vector Test: Vector2DToAngleRad = %f", Vector2DToAngleRad(&v));

		StreamClose(&file);

		// NOTE: This call causes the engine to exit immediately.  Make sure to remove
		//   it when you are ready to test out a new scene.
		SceneSystemSetNext(NULL);
	}
	else {
		printf("The file 'VectorTests.txt' was not opened\n");
	}
}

// Render any objects associated with the scene.
void SandboxSceneRender(void)
{
}

// Free any objects associated with the scene.
static void SandboxSceneExit()
{
}

// Unload any resources used by the scene.
static void SandboxSceneUnload(void)
{
}

/*
// Writes float values to the trace file.
static void SandboxSceneTraceFloat(const char* text, float f)
{
	// The trace message should be formatted as "Vector Test: %s = %f"
	TraceMessage("Vector Test: %s = %f", text, f);
}

// Writes Vector2D values to the trace file.
static void SandboxSceneTraceVector(const char* text, const Vector2D* v)
{
	// The trace message should be formatted as "Vector Test: %s = [%f, %f]"
	TraceMessage("Vector Test: %s = [%f, %f]", text, v->x, v->y);
}
*/
