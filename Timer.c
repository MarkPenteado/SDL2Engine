#include <stdio.h>
#include <stdlib.h>
#include "Timer.h"

Timer* createTimer(void) {
	Timer* newTimer = (Timer*)malloc(sizeof(Timer));
	if (newTimer == NULL) {
		printf("Error! newTimer could not initialize!\n");
		return NULL;
	}
	newTimer->ticks = 0.0;
	newTimer->seconds = 0.0;
	newTimer->frameIndex = 0.0;
	return newTimer;
}

void destroyTimer(Timer** timer) {
	if (*timer != NULL) {
		free(*timer);
		*timer = NULL;
	}
}

float countTimerTime(Timer** timer, Uint32 time, Uint32 maxCount) {
	if (*timer != NULL) {
		(*timer)->ticks = SDL_GetTicks();
		(*timer)->seconds = (*timer)->ticks / time;
		return ((*timer)->seconds % maxCount);
	}
	return 0.0;
}

void calculateTimerFrameIndex(Timer** timer, Uint32 animationVelocity, int frames) {
	if (*timer != NULL) {
		(*timer)->ticks = SDL_GetTicks();
		(*timer)->seconds = (*timer)->ticks / animationVelocity;
		(*timer)->frameIndex = (*timer)->seconds % frames;
	}
}

// get functions
Uint32 getTimerTicks(Timer* timer) {
	if (timer != NULL) {
		return timer->ticks;
	}

	return 0.0;
}

Uint32 getTimerSeconds(Timer* timer) {
	if (timer != NULL) {
		return timer->seconds;
	}

	return 0.0;
}

Uint32 getTimerFrameIndex(Timer* timer) {
	if (timer != NULL) {
		return timer->frameIndex;
	}

	return 0.0;
}

// set procedures
void setTimerTicks(Timer** timer, Uint32 ticks) {
	if (*timer != NULL) {
		(*timer)->ticks = ticks;
	}
}

void setTimerSeconds(Timer** timer, Uint32 seconds) {
	if (*timer != NULL) {
		(*timer)->seconds = seconds;
	}
}

void setTimerFrameIndex(Timer** timer, Uint32 frameIndex) {
	if (*timer != NULL) {
		(*timer)->frameIndex = frameIndex;
	}
}