#include <stdio.h>
#include <stdlib.h>
#include "Transition.h"

// transition functions
Transition* createTransition(float fadeSpeed) {
	Transition* newTransition = (Transition*)malloc(sizeof(Transition));
	if (newTransition == NULL) {
		printf("Error! newTransition could not initialize!\n");
		return NULL;
	}
	newTransition->spriteArray = NULL;
	if (fadeSpeed < 256) {
		newTransition->fadeSpeed = fadeSpeed;
	} else {
		newTransition->fadeSpeed = SDL_ALPHA_OPAQUE;
	}
	newTransition->spriteIndex = 0;
	return newTransition;
}

void destroyTransition(Transition** transition) {
	if (*transition != NULL) {
		if ((*transition)->spriteArray != NULL) {
			free((*transition)->spriteArray);
			(*transition)->spriteArray = NULL;
		}
		free(*transition);
		*transition = NULL;
	}
}

int addTransitionSprite(Transition** transition, Sprite** sprite) {
	if (*transition != NULL) {
		if ((*transition)->spriteArray == NULL) {
			(*transition)->spriteArray = (Sprite**)malloc(sizeof(Sprite*));
			if ((*transition)->spriteArray == NULL) {
				printf("Error! (*transition)->spriteArray could not initialize!\n");
				return -1;
			}
			(*transition)->spriteArray[(*transition)->spriteIndex] = sprite;
			(*transition)->spriteIndex++;
		} else {
			Sprite** tmpSpriteArrayRealloc = (Sprite**)realloc((*transition)->spriteArray, sizeof(Sprite*) * ((*transition)->spriteIndex + 1));
			if (*tmpSpriteArrayRealloc == NULL) {
				printf("Error! tmpSpriteArrayRealloc could not initialize!\n");
				return -1;
			}
			(*transition)->spriteArray = tmpSpriteArrayRealloc;
			(*transition)->spriteArray[(*transition)->spriteIndex] = sprite;
			(*transition)->spriteIndex++;
		}
		return 1;
	}
	return -1;
}

bool executeTransitionSpriteFadeOut(Transition** transition) {
	if (*transition != NULL) {
		Sprite** sprite;
		Uint8 alphaUint8;
		int i, j;
		float alpha;
		for (i = 0; i < (*transition)->spriteIndex; i++) {
			sprite = (*transition)->spriteArray[i];
			SDL_GetTextureAlphaMod((*sprite)->sdl_texture, &alphaUint8);
			alpha = alphaUint8;
			alpha -= (*transition)->fadeSpeed;
			if (alpha <= 0) {
				for (j = 0; j < (*transition)->spriteIndex; j++) {
					sprite = (*transition)->spriteArray[j];
					SDL_SetTextureAlphaMod((*sprite)->sdl_texture, 0);
				}
				return false;
			} else {
				SDL_SetTextureAlphaMod((*sprite)->sdl_texture, alpha);
			}
		}
		return true;
	}
	return false;
}

bool executeTransitionSpriteFadeIn(Transition** transition) {
	if (*transition != NULL) {
		Sprite** sprite;
		Uint8 alphaUint8;
		int i, j;
		float alpha;
		for (i = 0; i < (*transition)->spriteIndex; i++) {
			sprite = (*transition)->spriteArray[i];
			SDL_GetTextureAlphaMod((*sprite)->sdl_texture, &alphaUint8);
			alpha = alphaUint8;
			alpha += (*transition)->fadeSpeed;
			if (alpha >= SDL_ALPHA_OPAQUE) {
				for (j = 0; j < (*transition)->spriteIndex; j++) {
					sprite = (*transition)->spriteArray[j];
					SDL_SetTextureAlphaMod((*sprite)->sdl_texture, SDL_ALPHA_OPAQUE);
				}
				return false;
			} else {
				SDL_SetTextureAlphaMod((*sprite)->sdl_texture, alpha);
			}
		}
		return true;
	}
	return false;
}

// get functions
Sprite** getTransitionSpriteArray(Transition* transition) {
	if (transition != NULL) {
		return transition->spriteArray;
	}
	return NULL;
}

float getTransitionFadeSpeed(Transition* transition) {
	if (transition != NULL) {
		return transition->fadeSpeed;
	}
	return 0.0;
}

int getTransitionSpriteIndex(Transition* transition) {
	if (transition != NULL) {
		return transition->spriteIndex;
	}
	return 0;
}

// set procedures
void setTransitionSpriteArray(Transition** transition, Sprite** spriteArray) {
	if (*transition != NULL) {
		(*transition)->spriteArray = spriteArray;
	}
}

void setTransitionFadeSpeed(Transition** transition, float fadeSpeed) {
	if (*transition != NULL) {
		(*transition)->fadeSpeed = fadeSpeed;
	}
}

void setTransitionSpriteIndex(Transition** transition, int spriteIndex) {
	if (*transition != NULL) {
		(*transition)->spriteIndex = spriteIndex;
	}
}