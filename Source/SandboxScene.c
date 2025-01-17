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


static void SandboxSceneTraceFloat(const char* text, float f);
static void SandboxSceneTraceVector(const char* text, const Vector2D* v);


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

		// Run tests
		Vector2D v = { 4.0f, 3.0f };
		Vector2DZero(&v);
		SandboxSceneTraceVector("Vector2DZero", &v);
		Vector2DSet(&v, 1.5f, 1.0f);
		SandboxSceneTraceVector("Vector2DSet", &v);
		Vector2DNeg(&v, &v);
		SandboxSceneTraceVector("Vector2DNeg", &v);
		Vector2DAdd(&v, &v, &v);
		SandboxSceneTraceVector("Vector2DAdd", &v);
		Vector2DSub(&v, &v, &v);
		SandboxSceneTraceVector("Vector2DSub", &v);
		StreamReadVector2D(file, &v);
		SandboxSceneTraceVector("StreamReadVector2D", &v);
		Vector2DNormalize(&v, &v);
		SandboxSceneTraceVector("Vector2DNormalize", &v);
		float scale = StreamReadFloat(file);
		SandboxSceneTraceFloat("StreamReadFloat", scale);
		Vector2DScale(&v, &v, scale);
		SandboxSceneTraceVector("Vector2DScale", &v);
		Vector2DScaleAdd(&v, &v, scale, &v);
		SandboxSceneTraceVector("Vector2DScaleAdd", &v);
		Vector2DScaleSub(&v, &v, scale, &v);
		SandboxSceneTraceVector("Vector2DScaleSub", &v);
		SandboxSceneTraceFloat("Vector2DLength", Vector2DLength(&v));
		SandboxSceneTraceFloat("Vector2DSquareLength", Vector2DSquareLength(&v));
		Vector2D v2 = { 3.0f, 4.0f };
		StreamReadVector2D(file, &v);
		SandboxSceneTraceVector("StreamReadVector2D", &v);
		StreamReadVector2D(file, &v2);
		SandboxSceneTraceVector("StreamReadVector2D", &v2);
		SandboxSceneTraceFloat("Vector2DDistance", Vector2DDistance(&v, &v2));
		SandboxSceneTraceFloat("Vector2DSquareDistance", Vector2DSquareDistance(&v, &v2));
		SandboxSceneTraceFloat("Vector2DDotProduct", Vector2DDotProduct(&v, &v2));
		float angle = StreamReadFloat(file);
		SandboxSceneTraceFloat("StreamReadFloat", angle);
		Vector2DFromAngleDeg(&v, angle);
		SandboxSceneTraceVector("Vector2DFromAngleDeg", &v);
		angle = StreamReadFloat(file);
		SandboxSceneTraceFloat("StreamReadFloat", angle);
		Vector2DFromAngleRad(&v, angle);
		SandboxSceneTraceVector("Vector2DFromAngleRad", &v);
		SandboxSceneTraceFloat("Vector2DToAngleRad", Vector2DToAngleRad(&v));

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

