#include <stdio.h>
#include <stdlib.h>
#include "SpriteAnimation.h"

// SpriteAnimation functions
SpriteAnimation* createSpriteAnimation(Sprite* sprite) {
	SpriteAnimation* newSpriteAnimation = (SpriteAnimation*)malloc(sizeof(SpriteAnimation));
	if (newSpriteAnimation == NULL) {
		printf("Error! newSpriteAnimation could not initialize!\n");
		return NULL;
	}
	newSpriteAnimation->sprite = sprite;
	newSpriteAnimation->animationSrcRect = NULL;
	newSpriteAnimation->animationDstRect = (SDL_Rect) { 0, 0, 0, 0 };
	newSpriteAnimation->frames = 0;
	newSpriteAnimation->timerAnimation = createTimer();
	if (newSpriteAnimation->timerAnimation == NULL) {
		return NULL;
	}
	return newSpriteAnimation;
}

void destroySpriteAnimation(SpriteAnimation** spriteAnimation) {
	if (*spriteAnimation != NULL) {
		if ((*spriteAnimation)->sprite != NULL) {
			(*spriteAnimation)->sprite = NULL;
		}
		if ((*spriteAnimation)->animationSrcRect != NULL) {
			free((*spriteAnimation)->animationSrcRect);
			(*spriteAnimation)->animationSrcRect = NULL;
		}
		if ((*spriteAnimation)->timerAnimation != NULL) {
			destroyTimer(&((*spriteAnimation)->timerAnimation));
			(*spriteAnimation)->timerAnimation = NULL;
		}
		free(*spriteAnimation);
		*spriteAnimation = NULL;
	}
}

int addSpriteAnimationFrame(SpriteAnimation** spriteAnimation, int x, int y, int width, int height) {
	if (*spriteAnimation != NULL) {
		if ((*spriteAnimation)->animationSrcRect == NULL) {
			(*spriteAnimation)->animationSrcRect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
			if ((*spriteAnimation)->animationSrcRect == NULL) {
				printf("Error! (*spriteAnimation)->animationSrcRect could not initialize!\n");
				return -1;
			}
			(*spriteAnimation)->animationSrcRect[(*spriteAnimation)->frames].x = x;
			(*spriteAnimation)->animationSrcRect[(*spriteAnimation)->frames].y = y;
			(*spriteAnimation)->animationSrcRect[(*spriteAnimation)->frames].w = width;
			(*spriteAnimation)->animationSrcRect[(*spriteAnimation)->frames].h = height;
			(*spriteAnimation)->frames++;
		} else {
			SDL_Rect* tmpRectRealloc = (SDL_Rect*)realloc((*spriteAnimation)->animationSrcRect, sizeof(SDL_Rect) * ((*spriteAnimation)->frames + 1));
			if (tmpRectRealloc == NULL) {
				printf("Error! tmpRectRealloc could not initialize!\n");
				return -1;
			}
			(*spriteAnimation)->animationSrcRect = tmpRectRealloc;
			(*spriteAnimation)->animationSrcRect[(*spriteAnimation)->frames].x = x;
			(*spriteAnimation)->animationSrcRect[(*spriteAnimation)->frames].y = y;
			(*spriteAnimation)->animationSrcRect[(*spriteAnimation)->frames].w = width;
			(*spriteAnimation)->animationSrcRect[(*spriteAnimation)->frames].h = height;
			(*spriteAnimation)->frames++;
		}
		return 1;
	}
	return -1;
}

void drawSpriteAnimationOnIndex(Window** window, SpriteAnimation** spriteAnimation, int index, int dstX, int dstY, int ratioDstW, int ratioDstH) {
	if (*spriteAnimation != NULL) {
		if ((index > -1) && (index < (*spriteAnimation)->frames)) {
			(*spriteAnimation)->animationDstRect.x = dstX;
			(*spriteAnimation)->animationDstRect.y = dstY;
			int width = (*spriteAnimation)->animationSrcRect[index].w;
			int height = (*spriteAnimation)->animationSrcRect[index].h;
			(*spriteAnimation)->animationDstRect.w = width * ratioDstW;
			(*spriteAnimation)->animationDstRect.h = height * ratioDstH;
			SDL_RenderCopyEx((*window)->sdl_renderer, (*spriteAnimation)->sprite->sdl_texture, &((*spriteAnimation)->animationSrcRect[index]), &((*spriteAnimation)->animationDstRect), (*spriteAnimation)->sprite->angle, NULL, (*spriteAnimation)->sprite->flip);
			if ((*spriteAnimation)->sprite->showRect) {
				SDL_SetRenderDrawColor((*window)->sdl_renderer, (*spriteAnimation)->sprite->colorRect.r, (*spriteAnimation)->sprite->colorRect.g, (*spriteAnimation)->sprite->colorRect.b, (*spriteAnimation)->sprite->colorRect.a);
				SDL_RenderDrawRect((*window)->sdl_renderer, &((*spriteAnimation)->animationDstRect));
			}
		}
	}
}

void drawSpriteAnimation(Window** window, SpriteAnimation** spriteAnimation, Uint32 animationVelocity, int dstX, int dstY, int ratioDstW, int ratioDstH) {
	if (*spriteAnimation != NULL) {
		calculateTimerFrameIndex(&((*spriteAnimation)->timerAnimation), animationVelocity, (*spriteAnimation)->frames);
		(*spriteAnimation)->animationDstRect.x = dstX;
		(*spriteAnimation)->animationDstRect.y = dstY;
		int width = (*spriteAnimation)->animationSrcRect[getTimerFrameIndex((*spriteAnimation)->timerAnimation)].w;
		int height = (*spriteAnimation)->animationSrcRect[getTimerFrameIndex((*spriteAnimation)->timerAnimation)].h;
		(*spriteAnimation)->animationDstRect.w = width * ratioDstW;
		(*spriteAnimation)->animationDstRect.h = height * ratioDstH;
		SDL_RenderCopyEx((*window)->sdl_renderer, (*spriteAnimation)->sprite->sdl_texture, &((*spriteAnimation)->animationSrcRect[getTimerFrameIndex((*spriteAnimation)->timerAnimation)]), &((*spriteAnimation)->animationDstRect), (*spriteAnimation)->sprite->angle, NULL, (*spriteAnimation)->sprite->flip);
		if ((*spriteAnimation)->sprite->showRect) {
			SDL_SetRenderDrawColor((*window)->sdl_renderer, (*spriteAnimation)->sprite->colorRect.r, (*spriteAnimation)->sprite->colorRect.g, (*spriteAnimation)->sprite->colorRect.b, (*spriteAnimation)->sprite->colorRect.a);
			SDL_RenderDrawRect((*window)->sdl_renderer, &((*spriteAnimation)->animationDstRect));
		}
	}
}

// get functions
Sprite* getSpriteAnimationSprite(SpriteAnimation* spriteAnimation) {
	if (spriteAnimation != NULL) {
		return spriteAnimation->sprite;
	}

	return NULL;
}

SDL_Rect* getSpriteAnimationAnimationSrcRect(SpriteAnimation* spriteAnimation) {
	if (spriteAnimation != NULL) {
		return spriteAnimation->animationSrcRect;
	}

	return NULL;
}

SDL_Rect getSpriteAnimationAnimationDstRect(SpriteAnimation* spriteAnimation) {
	if (spriteAnimation != NULL) {
		return spriteAnimation->animationDstRect;
	}

	return (SDL_Rect) { 0, 0, 0, 0 };
}

Timer* getSpriteAnimationTimerAnimation(SpriteAnimation* spriteAnimation) {
	if (spriteAnimation != NULL) {
		return spriteAnimation->timerAnimation;
	}

	return NULL;
}

int getSpriteAnimationFrames(SpriteAnimation* spriteAnimation) {
	if (spriteAnimation != NULL) {
		return spriteAnimation->frames;
	}

	return 0;
}

// set procedures
void setSpriteAnimationSprite(SpriteAnimation** spriteAnimation, Sprite* sprite) {
	if (*spriteAnimation != NULL) {
		(*spriteAnimation)->sprite = sprite;
	}
}

void setSpriteAnimationAnimationSrcRect(SpriteAnimation** spriteAnimation, SDL_Rect* animationSrcRect) {
	if (*spriteAnimation != NULL) {
		(*spriteAnimation)->animationSrcRect = animationSrcRect;
	}
}

void setSpriteAnimationAnimationDstRect(SpriteAnimation** spriteAnimation, SDL_Rect animationDstRect) {
	if (*spriteAnimation != NULL) {
		(*spriteAnimation)->animationDstRect = animationDstRect;
	}
}

void setSpriteAnimationTimerAnimation(SpriteAnimation** spriteAnimation, Timer* timerAnimation) {
	if (*spriteAnimation != NULL) {
		(*spriteAnimation)->timerAnimation = timerAnimation;
	}
}

void setSpriteAnimationFrames(SpriteAnimation** spriteAnimation, int frames) {
	if (*spriteAnimation != NULL) {
		(*spriteAnimation)->frames = frames;
	}
}
