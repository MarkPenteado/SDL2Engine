#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

struct timer {
	Uint32 ticks;
	Uint32 seconds;
	Uint32 frameIndex;
};

typedef struct timer Timer;

// timer functions
Timer* createTimer(void);
void destroyTimer(Timer** timer);
float countTimerTime(Timer** timer, Uint32 time, Uint32 maxCount);
void calculateTimerFrameIndex(Timer** timer, Uint32 animationVelocity, int frames);

// get functions
Uint32 getTimerTicks(Timer* timer);
Uint32 getTimerSeconds(Timer* timer);
Uint32 getTimerFrameIndex(Timer* timer);

// set procedures
void setTimerTicks(Timer** timer, Uint32 ticks);
void setTimerSeconds(Timer** timer, Uint32 seconds);
void setTimerFrameIndex(Timer** timer, Uint32 frameIndex);

#endif // TIMER_H