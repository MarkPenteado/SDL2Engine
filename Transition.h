#ifndef TRANSITION_H
#define TRANSITION_H

#include <stdbool.h>
#include <SDL.h>
#include "Sprite.h"

struct transition {
	Sprite** spriteArray;
	float fadeSpeed;
	int spriteIndex;
};

typedef struct transition Transition;

// transition functions
Transition* createTransition(float fadeSpeed);
void destroyTransition(Transition** transition);
int addTransitionSprite(Transition** transition, Sprite** sprite);
bool executeTransitionSpriteFadeOut(Transition** transition);
bool executeTransitionSpriteFadeIn(Transition** transition);

// get functions
Sprite** getTransitionSpriteArray(Transition* transition);
float getTransitionFadeSpeed(Transition* transition);
int getTransitionSpriteIndex(Transition* transition);

// set procedures
void setTransitionSpriteArray(Transition** transition, Sprite** spriteArray);
void setTransitionFadeSpeed(Transition** transition, float fadeSpeed);
void setTransitionSpriteIndex(Transition** transition, int spriteIndex);

#endif // TRANSITION_H