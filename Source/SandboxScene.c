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

	// NOTE: This call causes the engine to exit immediately.  Make sure to remove
	//   it when you are ready to test out a new scene.
	SceneSystemSetNext(NULL);

	// Open the file, “Data/VectorTests.txt”, using StreamOpen()
	errno_t err = StreamOpen(&traceFile, traceFileName, "wt");

	// If the stream was opened successfully.
	if (err == 0) {

		// Create a single Vector2D variable for tests
		Vector2D v = { 4.0f, 3.0f };

		Vector2DZero(&v);
		StreamWrite(traceFile, "Vector2DZero: (%f, %f)\n", v.x, v.y);
		Vector2DSet(&v, 1.5f, 1.0f);
		StreamWrite(traceFile, "Vector2DSet: (%f, %f)\n", v.x, v.y);
		Vector2DNeg(&v, &v);
		StreamWrite(traceFile, "Vector2DNeg: (%f, %f)\n", v.x, v.y);
		Vector2DAdd(&v, &v, &v);
		StreamWrite(traceFile, "Vector2DAdd: (%f, %f)\n", v.x, v.y);
		Vector2DSub(&v, &v, &v);
		StreamWrite(traceFile, "Vector2DSub: (%f, %f)\n", v.x, v.y);
		StreamReadVector2D(&traceFile, &v);
		StreamWrite(traceFile, "StreamReadVector2D: (%f, %f)\n", v.x, v.y);
		Vector2DNormalize(&v, &v);
		StreamWrite(traceFile, "Vector2DNormalize: (%f, %f)\n", v.x, v.y);
		float scale = StreamReadFloat(&traceFile);
		StreamWrite(traceFile, "StreamReadFloat: (%f)\n", scale);
		Vector2DScale(&v, &v, scale);
		StreamWrite(traceFile, "Vector2DScale: (%f, %f)\n", v.x, v.y);
		Vector2DScaleAdd(&v, &v, scale, &v);
		StreamWrite(traceFile, "Vector2DScaleAdd: (%f, %f)\n", v.x, v.y);
		Vector2DScaleSub(&v, &v, scale, &v);
		StreamWrite(traceFile, "Vector2DScaleSub: (%f, %f)\n", v.x, v.y);
		Vector2DLength(&v);
		StreamWrite(traceFile, "Vector2DLength: (%f, %f)\n", v.x, v.y);
		Vector2DSquareLength(&v);
		StreamWrite(traceFile, "Vector2DSquareLength: (%f, %f)\n", v.x, v.y);


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
	TraceMessage("Vector Test: %s = %f", f);
}

// Writes Vector2D values to the trace file.
static void SandboxSceneTraceVector(const char* text, const Vector2D* v)
{
	// The trace message should be formatted as "Vector Test: %s = [%f, %f]"
	TraceMessage("Vector Test: %s = [%f, %f]", v);
}
