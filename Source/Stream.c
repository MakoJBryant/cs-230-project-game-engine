//------------------------------------------------------------------------------
//
// File Name:	Stream.c
// Author(s):	Mako J. Bryant (0068410)
// Project:		Project 1
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <stdio.h>
#include <string.h>

#include "Stream.h"
#include "Trace.h"

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

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Open a file for reading.
// (NOTE: Use fopen_s() with the "rt" option.)
// (NOTE: You must generate the following trace message if the file was not opened successfully:
//	  TraceMessage("Error: StreamOpen could not open file %s; %s", filePath, errorMsg);
//	  Where errorMsg is a char array containing the error message obtained using strerror_s().)
//    https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/strerror-s-strerror-s-wcserror-s-wcserror-s?view=msvc-170
// Params:
//	 filePath = The file to be opened for reading.
// Returns:
//	 NULL if filePath is NULL or the file could not be opened.
//	 Pointer to a FILE object if the file was opened successfully.
Stream StreamOpen(const char* filePath) {

	// NULL check.
	if (filePath == NULL) {
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

// Read a single integer from a stream.
// (NOTE: Verify that the stream is valid first.)
// (NOTE: Use fscanf_s() to scan the input stream for an integer.)
// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fscanf-s-fscanf-s-l-fwscanf-s-fwscanf-s-l?view=msvc-170
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 0 if the stream was not opened succesfully;
//	 otherwise, an integer value read from the file.
int StreamReadInt(Stream stream) {

	// NULL check.
	if (stream == NULL) {
		return 0;
	}

	int value;
	errno_t err = fscanf_s(stream, "%d", &value);

	// fscanf_s() error check.
	if (err != 1) {
		return 0;
	}

	// err == 1, no errors, 
	// return int value read from stream.
	return value;
}

// Read a single float from a stream.
// (NOTE: Verify that the stream is valid first.)
// (NOTE: Use fscanf_s() to scan the input stream for a float.)
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 If the stream was opened succesfully,
//	   then return a float value read from the file,
//	   else return 0.
float StreamReadFloat(Stream stream) {

	// NULL check.
	if (stream == NULL) {
		return 0;
	}

	float value;
	errno_t err = fscanf_s(stream, "%f", &value);

	// fscanf_s() error check.
	if (err != 1) {
		return 0;
	}

	// err == 1, no errors, 
	// return float value read from stream.
	return value;
}

// Read the data for a Vector2D from a stream.
// (NOTE: Verify that the stream and vector pointer are valid first.)
// (HINT: Use StreamReadFloat() to read the x and y values, in sequence.)
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 If the stream and vector pointer are both valid,
//	   then fill the vector with two float values (x & y),
//	   else do nothing (optionally, write an error message to the trace log).
void StreamReadVector2D(Stream stream, Vector2D* vector) {

	// (NOTE: Verify that the stream and vector pointer are valid first.)
	if (stream == NULL || vector == NULL) {
		TraceMessage("Error: %s or %s pointer(s) are NULL", stream, vector);
		return; // do nothing.
	}

	// (HINT: Use StreamReadFloat() to read the x and y values, in sequence.)
	vector->x = StreamReadFloat(stream);
	vector->y = StreamReadFloat(stream);

}

// Close an opened stream.
// (NOTE: Do not attempt to close the stream if the pointer is null.)
// (PRO TIP: Avoid dangling pointers by setting the FILE pointer to NULL.)
// Params:
//	 stream = The file stream to be closed.
void StreamClose(Stream* stream) {
	if (stream != NULL) {
		fclose(*stream);
		stream = NULL; // Avoid dangling pointers.
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

