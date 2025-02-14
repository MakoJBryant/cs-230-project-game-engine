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

// Dynamically allocate a new Animation component.
Animation* AnimationCreate(void)
{
	Animation* newAnimation = (Animation*)calloc(1, sizeof(Animation));
	if (!newAnimation) {
		TraceMessage("Error: AnimationCreate failed to allocate memory.");
		return NULL;
	}

	return newAnimation;
}

// Read the properties of an Animation component from a file.
void AnimationFree(Animation** animation)
{
	// Ensure the pointer is valid and not already NULL.
	if (animation == NULL || *animation == NULL) {
		TraceMessage("Error: AnimationFree received NULL argument(s).");
		return;
	}

	free(*animation);
	*animation = NULL;
}

// Read the properties of an Animation component from a file.
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
void AnimationSetParent(Animation* animation, Entity* parent)
{
	if (animation == NULL) {
		TraceMessage("Error: AnimationSetParent received NULL argument(s).");
		return;
	}

	animation->parent = parent;
}

// Play a simple animation sequence [0 .. frameCount - 1].
void AnimationPlay(Animation* animation, int frameCount, float frameDuration, bool isLooping)
{
	if (animation == NULL) {
		TraceMessage("Error: AnimationPlay received NULL argument(s).");
		return;
	}

	// (Hint: This function must initialize all variables, except for "parent".)
	animation->frameIndex = 0;
	animation->frameCount = frameCount;
	animation->frameDuration = frameDuration;
	animation->frameDelay = frameDuration;
	animation->isLooping = isLooping;
	animation->isRunning = true;
	animation->isDone = false;
}

// Update the animation.
void AnimationUpdate(Animation* animation, float dt)
{
	if (animation == NULL) {
		TraceMessage("Error: AnimationUpdate received NULL argument(s).");
		return;
	}

	// If the animation is not running, do nothing.
	if (!animation->isRunning) {
		return;
	}

	// Decrease the frame delay by dt.
	animation->frameDelay -= dt;

	// If the frame delay has elapsed, move to the next frame.
	while (animation->frameDelay <= 0.0f)
	{
		// Advance to the next frame.
		animation->frameIndex++;

		// Reset frame delay for the next frame.
		animation->frameDelay += animation->frameDuration;

		// Check if the animation has reached the end.
		if (animation->frameIndex >= animation->frameCount)
		{
			if (animation->isLooping)
			{
				// Loop back to the first frame.
				animation->frameIndex = 0;
			}
			else
			{
				// Stop the animation at the last frame.
				animation->frameIndex = animation->frameCount - 1;
				animation->isRunning = false;
				animation->isDone = true;
				break;
			}
		}
	}
}

// Determine if the animation has reached the end of its sequence.
bool AnimationIsDone(const Animation* animation)
{
	if (animation == NULL) {
		TraceMessage("Error: AnimationIsDone received NULL argument(s).");
		return false;
	}

	return animation->isDone;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
