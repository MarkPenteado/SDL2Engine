#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <SDL.h>
#include <SDL_image.h>
#include "Window.h"
#include "Sprite.h"
#include "Timer.h"

struct spriteAnimation {
	Sprite* sprite;
	SDL_Rect* animationSrcRect;
	SDL_Rect animationDstRect;
	Timer* timerAnimation;
	int frames;
};

typedef struct spriteAnimation SpriteAnimation;

// SpriteAnimation functions
SpriteAnimation* createSpriteAnimation(Sprite* sprite);
void destroySpriteAnimation(SpriteAnimation** spriteAnimation);
int addSpriteAnimationFrame(SpriteAnimation** spriteAnimation, int x, int y, int width, int height);
void drawSpriteAnimationOnIndex(Window** window, SpriteAnimation** spriteAnimation, int index, int dstX, int dstY, int ratioDstW, int ratioDstH);
void drawSpriteAnimation(Window** window, SpriteAnimation** spriteAnimation, Uint32 animationVelocity, int dstX, int dstY, int ratioDstW, int ratioDstH);

// get functions
Sprite* getSpriteAnimationSprite(SpriteAnimation* spriteAnimation);
SDL_Rect* getSpriteAnimationAnimationSrcRect(SpriteAnimation* spriteAnimation);
SDL_Rect getSpriteAnimationAnimationDstRect(SpriteAnimation* spriteAnimation);
Timer* getSpriteAnimationTimerAnimation(SpriteAnimation* spriteAnimation);
int getSpriteAnimationFrames(SpriteAnimation* spriteAnimation);

// set procedures
void setSpriteAnimationSprite(SpriteAnimation** spriteAnimation, Sprite* sprite);
void setSpriteAnimationAnimationSrcRect(SpriteAnimation** spriteAnimation, SDL_Rect* animationSrcRect);
void setSpriteAnimationAnimationDstRect(SpriteAnimation** spriteAnimation, SDL_Rect animationDstRect);
void setSpriteAnimationTimerAnimation(SpriteAnimation** spriteAnimation, Timer* timerAnimation);
void setSpriteAnimationFrames(SpriteAnimation** spriteAnimation, int frames);

#endif // SPRITE_ANIMATION_H