//------------------------------------------------------------------------------
//
// File Name:	Animation.c
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
#include "Animation.h"
#include "Stream.h"
#include "Trace.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Animation
{
	// Pointer to the parent Entity associated with the Animation component.
	Entity* parent;

	// The current frame being displayed.
	unsigned int frameIndex;

	// The maximum number of frames in the sequence.
	unsigned int frameCount;

	// The time remaining for the current frame.
	float frameDelay;

	// The amount of time to display each successive frame.
	float frameDuration;

	// True if the animation is running; false if the animation has stopped.
	bool isRunning;

	// True if the animation loops back to the beginning.
	bool isLooping;

	// True if the end of the animation sequence has been reached, false otherwise.
	// (Hint: This should be true for only one game loop.)
	bool isDone;

} Animation;

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

Animation* AnimationCreate(void)
{
	Animation* newAnimation = (Animation*)calloc(1, sizeof(Animation));
	if (!newAnimation) {
		TraceMessage("Error: AnimationCreate failed to allocate memory.");
		return NULL;
	}

	return newAnimation;
}

void AnimationFree(Animation** animation)
{
	// Ensure the pointer is valid and not already NULL.
	if (animation == NULL || *animation == NULL)
	{
		TraceMessage("Error: AnimationFree failed to allocate memory.");
		return;
	}

	free(*animation);
	*animation = NULL;
}

// Read the properties of an Animation component from a file.
// [NOTE: Read the integer values for frameIndex and frameCount.]
// [NOTE: Read the float values for frameDelay and frameDuration.]
// [NOTE: Read the boolean values for isRunning and isLooping.]
// Params:
//	 animation = Pointer to the Animation component.
//	 stream = The data stream used for reading.
void AnimationRead(Animation* animation, Stream stream)
{
	if (animation == NULL || stream == NULL) {
		TraceMessage("Error: AnimationRead received NULL argument(s).");
		return;
	}

	// Read integer values.
	animation->frameIndex = StreamReadInt(stream);
	animation->frameCount = StreamReadInt(stream);

	// Read float values.
	animation->frameDelay = StreamReadFloat(stream);
	animation->frameDuration = StreamReadFloat(stream);

	// Read boolean values.
	animation->isRunning = StreamReadBoolean(stream);
	animation->isLooping = StreamReadBoolean(stream);
}

// Set the parent Entity for an Animation component.
// Params:
//	 animation = Pointer to the Animation component.
//	 parent = Pointer to the parent Entity.
void AnimationSetParent(Animation* animation, Entity* parent)
{
	UNREFERENCED_PARAMETER(animation);
	UNREFERENCED_PARAMETER(parent);
}

// Play a simple animation sequence [0 .. frameCount - 1].
// (Hint: This function must initialize all variables, except for "parent".)
// Params:
//	 animation = Pointer to the Animation component.
//	 frameCount = The number of frames in the sequence.
//	 frameDuration = The amount of time to display each frame (in seconds).
//	 isLooping = True if the animation loops, false otherwise.
void AnimationPlay(Animation* animation, int frameCount, float frameDuration, bool isLooping)
{
	UNREFERENCED_PARAMETER(animation);
	UNREFERENCED_PARAMETER(frameCount);
	UNREFERENCED_PARAMETER(frameDuration);
	UNREFERENCED_PARAMETER(isLooping);
}

// Update the animation.
// Params:
//	 animation = Pointer to the Animation component.
//	 dt = Change in time (in seconds) since the last game loop.
void AnimationUpdate(Animation* animation, float dt)
{
	UNREFERENCED_PARAMETER(animation);
	UNREFERENCED_PARAMETER(dt);
}

// Determine if the animation has reached the end of its sequence.
// Params:
//	 animation = Pointer to the Animation component.
// Returns:
//	 If the Animation pointer is valid,
//		then return the value in isDone,
//		else return false.
bool AnimationIsDone(const Animation* animation)
{
	UNREFERENCED_PARAMETER(animation);
	return 0;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

