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

#include "stdafx.h"
#include "Matrix2D.h"

#include "DGL.h"

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
	if (!pResult) return;

	// Set all elements to zero
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j) {
				// Set diagonal elements to 1
				pResult->m[i][j] = 1.0f; 
			} 
			else {
				// Set non-diagonal elements to 0
				pResult->m[i][j] = 0.0f;
			}
		}
	}
}

// This function calculates the transpose matrix of Mtx and saves it in the result matrix.
// (NOTE: Care must be taken when pResult = pMtx.)
void Matrix2DTranspose(Matrix2D* pResult, const Matrix2D* pMtx)
{
	UNREFERENCED_PARAMETER(pResult);
	UNREFERENCED_PARAMETER(pMtx);
}

// This function multiplies Mtx0 with Mtx1 and saves the result in Result.
// Result = Mtx0*Mtx1
// (NOTE: Care must be taken when pResult = either pMtx0 or pMtx1.)
void Matrix2DConcat(Matrix2D* pResult, const Matrix2D* pMtx0, const Matrix2D* pMtx1)
{
	UNREFERENCED_PARAMETER(pResult);
	UNREFERENCED_PARAMETER(pMtx0);
	UNREFERENCED_PARAMETER(pMtx1);
}

// This function creates a translation matrix from x & y and saves it in Result.
// (Hint: This function must initialize all matrix values.)
void Matrix2DTranslate(Matrix2D* pResult, float x, float y)
{
	UNREFERENCED_PARAMETER(pResult);
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);
}

// This function creates a scaling matrix from x & y and saves it in Result.
// (Hint: This function must initialize all matrix values.)
void Matrix2DScale(Matrix2D* pResult, float x, float y)
{
	UNREFERENCED_PARAMETER(pResult);
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);
}

// This matrix creates a rotation matrix from "Angle" whose value is in degrees.
// (Hint: This function must initialize all matrix values.)
// Converting from degrees to radians can be performed as follows:
//	 radians = (angle * M_PI) / 180.0f
// M_PI is defined in "math.h", which may be included as follows:
//   #define _USE_MATH_DEFINES
//   #include <math.h>
void Matrix2DRotDeg(Matrix2D* pResult, float angle)
{
	UNREFERENCED_PARAMETER(pResult);
	UNREFERENCED_PARAMETER(angle);
}

// This matrix creates a rotation matrix from "Angle" whose value is in radians.
// (Hint: This function must initialize all matrix values.)
void Matrix2DRotRad(Matrix2D* pResult, float angle)
{
	UNREFERENCED_PARAMETER(pResult);
	UNREFERENCED_PARAMETER(angle);
}

// This function multiplies the matrix Mtx with the vector Vec and saves the result in Result.
// Result = Mtx * Vec.
// (NOTE: Care must be taken when pResult = pVec.)
// (NOTE: Remember to treat the implied w component as 1.)
void Matrix2DMultVec(Vector2D* pResult, const Matrix2D* pMtx, const Vector2D* pVec)
{
	UNREFERENCED_PARAMETER(pResult);
	UNREFERENCED_PARAMETER(pMtx);
	UNREFERENCED_PARAMETER(pVec);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

