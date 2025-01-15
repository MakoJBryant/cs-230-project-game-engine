//------------------------------------------------------------------------------
//
// File Name:	stdafx.c
// Author(s):	Matthew Picioccio (mattpic), Doug Schilling (dschilling)
// Project:		Project 0
// Course:		CS230S25
// Purpose:		This file includes standard system include files, or project-specific 
//   include files that are used frequently, but are changed infrequently.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

// Disable warnings for single-line comments, since Microsoft's stdlib, etc. use those extensively.
#pragma warning(push)
#pragma warning(disable : 4001)

#include "targetver.h" /* required by Windows */

#include <stdlib.h> /* NULL, malloc/free */
#include <stdio.h> /* printf, fgets */
#include <stdbool.h> /* bool */
#include <string.h> /* strcmp, strcpy_s, strtok_s */
#include <winerror.h>

// Used to clean /W4 unused parameters for functions that must match a function-pointer type 
// NOTE: copied from winnt.h, but we don't want to include that here, otherwise.
#define UNREFERENCED_PARAMETER(P) (P)

// Pop the warning-disable
#pragma warning(pop)