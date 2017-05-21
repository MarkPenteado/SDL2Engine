#ifndef FPS_H
#define FPS_H

#include <SDL.h>

struct fps {
	float alpha; // Lower means smoother, but higher values respond faster. default: 0.2
	Uint32 getticks;
	Uint32 frametimedelta;
	Uint32 frametimelast;
	float frametime;
	float framespersecond;
	Uint32 currentTime;
};

typedef struct fps FPS;

// FPS functions
FPS* createFPS(float alpha);
void destroyFPS(FPS** fps);
void calculateFPS(FPS** fps); // This method uses weighted averaging of the current measurement with the previous estimate.
void applyFPS(FPS* fps, float fpsInterval); // Cap the fps
void setFPSStartCurrentTime(FPS** fps); // It should be applied at the beginning of the main loop

// get functions
float getFPSAlpha(FPS* fps);
Uint32 getFPSFrameTimeDelta(FPS* fps);
Uint32 getFPSGetTicks(FPS* fps);
Uint32 getFPSFrameTimeLast(FPS* fps);
float getFPSFrameTime(FPS* fps);
float getFPSFramesPerSecond(FPS* fps);
Uint32 getFPSCurrentTime(FPS* fps);

// set procedures
void setFPSAlpha(FPS** fps, float alpha);
void setFPSFrameTimeDelta(FPS** fps, Uint32 frametimedelta);
void setFPSGetTicks(FPS** fps, Uint32 getticks);
void setFPSFrameTimeLast(FPS** fps, Uint32 frametimelast);
void setFPSFrameTime(FPS** fps, float frametime);
void setFPSFramesPerSecond(FPS** fps, float framespersecond);
void setFPSCurrentTime(FPS** fps, Uint32 currentTime);

#endif // FPS_H