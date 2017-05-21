#include <stdio.h>
#include <stdlib.h>
#include "FPS.h"

FPS* createFPS(float alpha) {
	FPS* newFps = (FPS*)malloc(sizeof(FPS));
	if (newFps == NULL) {
		printf("Error! newFps could not initialize!\n");
		return NULL;
	}
	newFps->alpha = alpha;
	newFps->getticks = 0;
	newFps->frametimedelta = 0;
	newFps->frametimelast = 0;
	newFps->frametime = 0;
	newFps->framespersecond = 0;
	newFps->currentTime = 0;
	return newFps;
}

void destroyFPS(FPS** fps) {
	if (*fps != NULL) {
		free(*fps);
		*fps = NULL;
	}
}

void calculateFPS(FPS** fps) {
	if (*fps != NULL) {
		(*fps)->getticks = SDL_GetTicks();
		(*fps)->frametimedelta = (*fps)->getticks - (*fps)->frametimelast;
		(*fps)->frametimelast = (*fps)->getticks;
		(*fps)->frametime = (*fps)->alpha * (*fps)->frametimedelta + (1.0 - (*fps)->alpha) * (*fps)->frametime;
		(*fps)->framespersecond = 1000.0 / (*fps)->frametime;
	}
}

void applyFPS(FPS* fps, float fpsInterval) {
	if (fps != NULL) {
		if ((SDL_GetTicks() - fps->currentTime) < 1000.0 / fpsInterval) {
			SDL_Delay((1000.0 / fpsInterval) - (SDL_GetTicks() - fps->currentTime));
		}
	}
}

void setFPSStartCurrentTime(FPS** fps) {
	if (*fps != NULL) {
		(*fps)->currentTime = SDL_GetTicks();
	}
}

// get functions
float getFPSAlpha(FPS* fps) {
	if (fps != NULL) {
		return fps->alpha;
	}

	return -1;
}

Uint32 getFPSFrameTimeDelta(FPS* fps) {
	if (fps != NULL) {
		return fps->frametimedelta;
	}

	return -1;
}

Uint32 getFPSGetTicks(FPS* fps) {
	if (fps != NULL) {
		return fps->getticks;
	}

	return -1;
}

Uint32 getFPSFrameTimeLast(FPS* fps) {
	if (fps != NULL) {
		return fps->frametimelast;
	}

	return -1;
}

float getFPSFrameTime(FPS* fps) {
	if (fps != NULL) {
		return fps->frametime;
	}

	return -1;
}

float getFPSFramesPerSecond(FPS* fps) {
	if (fps != NULL) {
		return fps->framespersecond;
	}

	return -1;
}

Uint32 getFPSCurrentTime(FPS* fps) {
	if (fps != NULL) {
		return fps->currentTime;
	}

	return 0.0;
}

// set procedures
void setFPSAlpha(FPS** fps, float alpha) {
	if (*fps != NULL) {
		(*fps)->alpha = alpha;
	}
}

void setFPSFrameTimeDelta(FPS** fps, Uint32 frametimedelta) {
	if (*fps != NULL) {
		(*fps)->frametimedelta = frametimedelta;
	}
}

void setFPSGetTicks(FPS** fps, Uint32 getticks) {
	if (*fps != NULL) {
		(*fps)->getticks = getticks;
	}
}

void setFPSFrameTimeLast(FPS** fps, Uint32 frametimelast) {
	if (*fps != NULL) {
		(*fps)->frametimelast = frametimelast;
	}
}

void setFPSFrameTime(FPS** fps, float frametime) {
	if (*fps != NULL) {
		(*fps)->frametime = frametime;
	}
}

void setFPSFramesPerSecond(FPS** fps, float framespersecond) {
	if (*fps != NULL) {
		(*fps)->framespersecond = framespersecond;
	}
}

void setFPSCurrentTime(FPS** fps, Uint32 currentTime) {
	if (*fps != NULL) {
		(*fps)->currentTime = currentTime;
	}
}