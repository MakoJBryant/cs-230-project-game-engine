//------------------------------------------------------------------------------
//
// File Name:	Stream.c
// Author(s):	Mako J. Bryant (mako.bryant)
// Project:		Project 1
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
#include "Stream.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h> // bool
#include "Trace.h"
#include "DGL.h" // Vector2D

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
static char tokenBuffer[1024];

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Open a file for reading.
Stream StreamOpen(const char* filePath) {

	if (filePath == NULL) {
		TraceMessage("Error: StreamOpen received NULL argument(s).");
		return NULL;
	}

	Stream file;
	errno_t err = fopen_s(&file, filePath, "rt");

	// fopen_s() error check.
	if (err != 0) {
		char errorMsg[256];
		strerror_s(errorMsg, sizeof(errorMsg), err);
		TraceMessage("Error: StreamOpen could not open file %s; %s", filePath, errorMsg);
		return NULL;
	}

	// err == 0, no errors, return file.
	return file;
}

// Read a single boolean value from a stream.
bool StreamReadBoolean(Stream stream)
{
	if (stream == NULL) { // (NOTE: Verify that the stream is valid first.)
		TraceMessage("Error: StreamReadBoolean received NULL argument(s).");
		return false;
	}

	int value; // (NOTE: Use fscanf_s() to scan the input stream for an integer.)
	errno_t err = fscanf_s(stream, "%d", &value);

	// fscanf_s() error check.
	if (err != 1) {
		TraceMessage("Error: StreamReadBoolean stream failed to open.");
		return false;
	}

	// Return true if value is nonzero, otherwise false.
	return value != 0;
}

// Read a single integer from a stream.
int StreamReadInt(Stream stream) {

	if (stream == NULL) {
		TraceMessage("Error: StreamReadInt received NULL argument(s).");
		return 0;
	}

	int value;
	errno_t err = fscanf_s(stream, "%d", &value);

	// fscanf_s() error check.
	if (err != 1) {
		TraceMessage("Error: StreamReadInt stream failed to open.");
		return 0;
	}

	// err == 1, no errors, 
	// return int value read from stream.
	return value;
}

// Read a single float from a stream.
float StreamReadFloat(Stream stream) {

	if (stream == NULL) {
		TraceMessage("Error: StreamReadFloat received NULL argument(s).");
		return 0.0f;
	}

	float value;
	errno_t err = fscanf_s(stream, "%f", &value);

	// fscanf_s() error check.
	if (err != 1) {
		TraceMessage("Error: StreamReadFloat stream failed to open.");
		return 0.0f;
	}

	// err == 1, no errors, 
	// return float value read from stream.
	return value;
}

// Read the data for a Vector2D from a stream.
void StreamReadVector2D(Stream stream, Vector2D* vector) 
{
	if (stream == NULL || vector == NULL) {
		TraceMessage("Error: StreamReadVector2D received NULL argument(s).");
		return;
	}

	vector->x = StreamReadFloat(stream);
	vector->y = StreamReadFloat(stream);
}

// Read a token (a single word) from a file.
const char* StreamReadToken(Stream stream)
{
	if (stream == NULL) {
		TraceMessage("Error: StreamReadToken argument(s) NULL.");
		return NULL;
	}

	// Clear buffer because it might contain old data from a previous read.
	tokenBuffer[0] = '\0';

	// The %1023s limits the input to 1023 chars (to prevent overflows).
	int result = fscanf_s(stream, "%1023s", tokenBuffer, (unsigned)_countof(tokenBuffer));

	// If fscanf_s returned no errors:
	if (result == 1) {
		// Return the value read into the buffer.
		return tokenBuffer;
	}
	else {
		return NULL;
	}

}

// Close an opened stream.
void StreamClose(Stream* stream)
{
	if (stream == NULL) {
		TraceMessage("Error: StreamClose received NULL argument(s).");
		return;
	}

	fclose(*stream);
	*stream = NULL;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

