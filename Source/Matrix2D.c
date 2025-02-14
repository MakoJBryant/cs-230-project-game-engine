//------------------------------------------------------------------------------
//
// File Name:	Matrix2D.c
// Author(s):	Mako J. Bryant (0068410)
// Project:		Project 3
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
#include "Matrix2D.h"
#include "DGL.h" // For DGL_Mat4
#include "Trace.h"
#define _USE_MATH_DEFINES // For M_PI, must be before math.h
#include <math.h>  // For trig functions

//------------------------------------------------------------------------------

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

// This function sets the matrix equal to the identity matrix.
void Matrix2DIdentity(Matrix2D* pResult)
{
	if (!pResult) {
		TraceMessage("Error: Matrix2DIdentity received NULL argument(s).");
		return;
	}

	for (int i = 0; i < 4; i++) // ROWs
	{
		for (int j = 0; j < 4; j++) // COLUMNs
		{
			if (i == j) {
				// Set diagonal elements to 1.0f
				pResult->m[i][j] = 1.0f;
			}
			else {
				// Set all off-diagonal elements to 0.0f
				pResult->m[i][j] = 0.0f;
			}
		}
	}
}

// This function calculates the transpose matrix of Mtx and saves it in the result matrix.
void Matrix2DTranspose(Matrix2D* pResult, const Matrix2D* pMtx)
{
	if (!pResult || !pMtx) {
		TraceMessage("Error: Matrix2DTranspose received NULL argument(s).");
		return;
	}

	Matrix2D temp; // Temporary matrix to store the result

	for (int i = 0; i < 4; i++) // ROWs
	{
		for (int j = 0; j < 4; j++) // COLUMNs
		{
			// Swap rows and columns
			temp.m[i][j] = pMtx->m[j][i];
		}
	}

	// Copy the result back to pResult
	*pResult = temp;
}

// This function multiplies Mtx0 with Mtx1 and saves the result in Result.
void Matrix2DConcat(Matrix2D* pResult, const Matrix2D* pMtx0, const Matrix2D* pMtx1)
{
	if (!pResult || !pMtx0 || !pMtx1) {
		TraceMessage("Error: Matrix2DConcat received NULL argument(s).");
		return;
	}

	Matrix2D temp; // Temporary matrix to store the result

	for (int i = 0; i < 4; i++) // ROWs
	{
		for (int j = 0; j < 4; j++) // COLUMNs
		{
			// Perform matrix multiplication between two 4x4 matrices
			temp.m[i][j] =
				  Matrix2DRowCol(pMtx0, i, 0) * Matrix2DRowCol(pMtx1, 0, j)	// first term
				+ Matrix2DRowCol(pMtx0, i, 1) * Matrix2DRowCol(pMtx1, 1, j)	// second term
				+ Matrix2DRowCol(pMtx0, i, 2) * Matrix2DRowCol(pMtx1, 2, j)	// third term
				+ Matrix2DRowCol(pMtx0, i, 3) * Matrix2DRowCol(pMtx1, 3, j);// fourth term
		}
	}

	// Copy the result back to pResult
	*pResult = temp;
}

// This function creates a translation matrix from x & y and saves it in Result.
void Matrix2DTranslate(Matrix2D* pResult, float x, float y)
{
	if (!pResult) {
		TraceMessage("Error: Matrix2DTranslate received NULL argument(s).");
		return;
	}

	// Initialize identity matrix
	Matrix2DIdentity(pResult);

	// Set translation values
	pResult->m[0][3] = x;
	pResult->m[1][3] = y;
}

// This function creates a scaling matrix from x & y and saves it in Result.
void Matrix2DScale(Matrix2D* pResult, float x, float y)
{
	if (!pResult) {
		TraceMessage("Error: Matrix2DScale received NULL argument(s).");
		return;
	}

	// Initialize identity matrix
	Matrix2DIdentity(pResult);

	// Set scaling values
	pResult->m[0][0] = x;
	pResult->m[1][1] = y;
}

// This matrix creates a rotation matrix from "Angle" whose value is in degrees.
void Matrix2DRotDeg(Matrix2D* pResult, float angle)
{
	if (!pResult) {
		TraceMessage("Error: Matrix2DRotDeg received NULL argument(s).");
		return;
	}

	// Convert angle from degrees to radians
	float radians = (angle * (float)M_PI) / 180.0f;

	// Initialize identity matrix
	Matrix2DIdentity(pResult);

	// Set rotation values
	pResult->m[0][0] = cosf(radians);
	pResult->m[0][1] = -sinf(radians);
	pResult->m[1][0] = sinf(radians);
	pResult->m[1][1] = cosf(radians);
}

// This matrix creates a rotation matrix from "Angle" whose value is in radians.
void Matrix2DRotRad(Matrix2D* pResult, float angle)
{
	if (!pResult) {
		TraceMessage("Error: Matrix2DRotRad received NULL argument(s).");
		return;
	}

	// Initialize identity matrix
	Matrix2DIdentity(pResult);

	// Set rotation values
	pResult->m[0][0] = cosf(angle);
	pResult->m[0][1] = -sinf(angle);
	pResult->m[1][0] = sinf(angle);
	pResult->m[1][1] = cosf(angle);
}

// This function multiplies the matrix Mtx with the vector Vec and saves the result in Result.
void Matrix2DMultVec(Vector2D* pResult, const Matrix2D* pMtx, const Vector2D* pVec)
{
	if (!pResult || !pMtx || !pVec) {
		TraceMessage("Error: Matrix2DMultVec received NULL argument(s).");
		return;
	}

	pResult->x =
		  Matrix2DRowCol(pMtx, 0, 0) * pVec->x	// scales the x-component of the vector
		+ Matrix2DRowCol(pMtx, 0, 1) * pVec->y	// scales the y-component of the vector
		+ Matrix2DRowCol(pMtx, 0, 3);			// adds translation in the x-direction

	pResult->y =
		  Matrix2DRowCol(pMtx, 1, 0) * pVec->x	// scales the x-component of the vector
		+ Matrix2DRowCol(pMtx, 1, 1) * pVec->y	// scales the y-component of the vector
		+ Matrix2DRowCol(pMtx, 1, 3);			// adds translation in the y-direction
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
