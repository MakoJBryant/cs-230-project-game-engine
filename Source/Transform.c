//------------------------------------------------------------------------------
//
// File Name:	Transform.c
// Author(s):	Mako J. Bryant (0068410)
// Project:		Project 2
// Course:		CS230S25
//
// Copyright � 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Transform.h"
#include "DGL.h"
#include "Trace.h"
#include "Stream.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Transform
{
	// The translation (or world position) of an entity.
	Vector2D	translation;

	// The rotation (or orientation) of an entity (in radians).
	float	rotation;

	// The scale (or size) of an entity.
	// (Hint: This should be initialized to (1, 1).)
	Vector2D	scale;

} Transform;

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

// Dynamically allocate a new Transform component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (Hint: You must initialize the scale values to non-zero values.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
Transform* TransformCreate(void)
{
	// malloc writes garbage for init, calloc writes 0's for init.
	Transform* newTransform = calloc(1, sizeof(Transform));

	// Verify that arguments are valid.
	if (newTransform == NULL) {
		TraceMessage("Error: TransformCreate failed to allocate memory.");
		return NULL;
	}

	// Set default scale to (1, 1).
	newTransform->scale.x = 1;
	newTransform->scale.y = 1;

	return newTransform;
}

// Free the memory associated with a Transform component.
// (NOTE: The Transform pointer must be set to NULL.)
// Params:
//	 transform = Pointer to the Transform pointer.
void TransformFree(Transform** transform)
{
	// Verify that arguments are valid.
	if (transform == NULL || *transform == NULL) {
		TraceMessage("Error: TransformFree received NULL argument(s).");
		return;
	}

	// Free object and nullify dangling pointer.
	free(*transform);
	*transform = NULL;
}

// Read the properties of a Transform component from a file.
// [NOTE: Read the translation value using StreamReadVector2D.]
// [NOTE: Read the rotation value using StreamReadFloat.]
// [NOTE: Read the scale value using StreamReadVector2D.]
// Params:
//	 transform = Pointer to the Transform component.
//	 stream = The data stream used for reading.
void TransformRead(Transform* transform, Stream stream)
{
	// Verify that arguments are valid.
	if (transform == NULL || stream == NULL) {
		TraceMessage("Error: TransformRead received NULL argument(s).");
		return;
	}

	// Translation.
	Vector2D tempTranslation;
	StreamReadVector2D(stream, &tempTranslation);
	TransformSetTranslation(transform, &tempTranslation);

	// Rotation.
	float tempRotation;
	tempRotation = StreamReadFloat(stream);
	TransformSetRotation(transform, tempRotation);

	// Scale.
	Vector2D tempScale;
	StreamReadVector2D(stream, &tempScale);
	TransformSetScale(transform, &tempScale);
}

// Get the translation of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
// Returns:
//	 If the Transform pointer is valid,
//		then return a pointer to the component's translation,
//		else return a NULL pointer.
const Vector2D* TransformGetTranslation(const Transform* transform)
{
	// Verify that arguments are valid.
	if (transform == NULL) {
		TraceMessage("Error: TransformGetTranslation received NULL argument(s).");
		return NULL;
	}

	return &transform->translation;
}

// Get the rotation value of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
// Returns:
//	 If the Transform pointer is valid,
//		then return the component's rotation value (in radians),
//		else return 0.0f.
float TransformGetRotation(const Transform* transform)
{
	// Verify that arguments are valid.
	if (transform == NULL) {
		TraceMessage("Error: TransformGetRotation received NULL argument(s).");
		return 0.0f;
	}

	return transform->rotation;
}

// Get the scale of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
// Returns:
//	 If the Transform pointer is valid,
//		then return a pointer to the component's scale,
//		else return a NULL pointer.
const Vector2D* TransformGetScale(const Transform* transform)
{
	// Verify that arguments are valid.
	if (transform == NULL) {
		TraceMessage("Error: TransformGetScale received NULL argument(s).");
		return NULL;
	}

	return &transform->scale;
}

// Set the translation of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
//	 translation = Pointer to the new translation.
void TransformSetTranslation(Transform* transform, const Vector2D* translation)
{
	// Verify that arguments are valid.
	if (transform == NULL || translation == NULL) {
		TraceMessage("Error: TransformSetTranslation received NULL argument(s).");
		return;
	}

	transform->translation = *translation;
}

// Set the rotation of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
//	 rotation = The rotation value (in radians).
void TransformSetRotation(Transform* transform, float rotation)
{
	// Verify that arguments are valid.
	if (transform == NULL) {
		TraceMessage("Error: TransformSetRotation received NULL argument(s).");
		return;
	}

	transform->rotation = rotation;
}

// Set the scale of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
//	 translation = Pointer to the new scale.
void TransformSetScale(Transform* transform, const Vector2D* scale)
{
	// Verify that arguments are valid.
	if (transform == NULL || scale == NULL) {
		TraceMessage("Error: TransformSetScale received NULL argument(s).");
		return;
	}

	transform->scale = *scale;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

