#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sprite.h"

// Sprite functions
Sprite* createSprite(Window** window, char* spritePath, int width, int height) {
	Sprite* newSprite = (Sprite*)malloc(sizeof(Sprite));
	if (newSprite == NULL) {
		printf("Error! newSprite could not initialize!\n");
		return NULL;
	}
	newSprite->spritePath = (char*)malloc(sizeof(char) * (strlen(spritePath) + 1));
	if (newSprite->spritePath == NULL) {
		printf("Error! newSprite->spritePath could not initialize!\n");
		return NULL;
	}
	strcpy(newSprite->spritePath, spritePath);
	newSprite->sdl_surface = IMG_Load(newSprite->spritePath);
	if (newSprite->sdl_surface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", newSprite->spritePath, IMG_GetError());
		return NULL;
	}
	newSprite->sdl_texture = SDL_CreateTextureFromSurface((*window)->sdl_renderer, newSprite->sdl_surface);
	if (newSprite->sdl_texture == NULL) {
		printf("Error! (*sprite)->sdl_texture could not initialize!\n");
		return NULL;
	}
	newSprite->sdl_srcRect = (SDL_Rect) { 0, 0, 0, 0 };
	newSprite->sdl_dstRect = (SDL_Rect) { 0, 0, width, height };
	newSprite->flip = SDL_FLIP_NONE; // SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL
	newSprite->angle = 0.0;
	newSprite->colorRect = (SDL_Color) { 0, 0, 0, 0 };
	newSprite->showRect = false;
	return newSprite;
}

void drawSpriteFull(Window** window, Sprite** sprite, int x, int y) {
	if (*sprite != NULL) {
		(*sprite)->sdl_dstRect.x = x;
		(*sprite)->sdl_dstRect.y = y;
		SDL_RenderCopyEx((*window)->sdl_renderer, (*sprite)->sdl_texture, NULL, &((*sprite)->sdl_dstRect), (*sprite)->angle, NULL, (*sprite)->flip);
		if ((*sprite)->showRect) {
			SDL_SetRenderDrawColor((*window)->sdl_renderer, (*sprite)->colorRect.r, (*sprite)->colorRect.g, (*sprite)->colorRect.b, (*sprite)->colorRect.a);
			SDL_RenderDrawRect((*window)->sdl_renderer, &((*sprite)->sdl_dstRect));
		}
	}
}

void destroySprite(Sprite** sprite) {
	if (*sprite != NULL) {
		if ((*sprite)->sdl_surface != NULL) {
			SDL_FreeSurface((*sprite)->sdl_surface);
			(*sprite)->sdl_surface = NULL;
		}
		if ((*sprite)->sdl_texture != NULL) {
			SDL_DestroyTexture((*sprite)->sdl_texture);
			(*sprite)->sdl_texture = NULL;
		}
		if ((*sprite)->spritePath != NULL) {
			free((*sprite)->spritePath);
			(*sprite)->spritePath = NULL;
		}
		free(*sprite);
		*sprite = NULL;
	}
}

void drawSprite(Window** window, Sprite** sprite, int spriteX, int spriteY, int spriteWidth, int spriteHeight, int drawX, int drawY, int drawWidth, int drawHeight) {
	if (*sprite != NULL) {
		(*sprite)->sdl_srcRect.x = spriteX;
		(*sprite)->sdl_srcRect.y = spriteY;
		(*sprite)->sdl_srcRect.w = spriteWidth;
		(*sprite)->sdl_srcRect.h = spriteHeight;
		(*sprite)->sdl_dstRect.x = drawX;
		(*sprite)->sdl_dstRect.y = drawY;
		(*sprite)->sdl_dstRect.w = drawWidth;
		(*sprite)->sdl_dstRect.h = drawHeight;
		SDL_RenderCopyEx((*window)->sdl_renderer, (*sprite)->sdl_texture, &((*sprite)->sdl_srcRect), &((*sprite)->sdl_dstRect), (*sprite)->angle, NULL, (*sprite)->flip);
		if ((*sprite)->showRect) {
			SDL_SetRenderDrawColor((*window)->sdl_renderer, (*sprite)->colorRect.r, (*sprite)->colorRect.g, (*sprite)->colorRect.b, (*sprite)->colorRect.a);
			SDL_RenderDrawRect((*window)->sdl_renderer, &((*sprite)->sdl_dstRect));
		}
	}
}

// get functions
SDL_Surface* getSpriteSdlSurface(Sprite* sprite) {
	if (sprite != NULL) {
		return sprite->sdl_surface;
	}

	return NULL;
}

SDL_Texture* getSpriteSdlTexture(Sprite* sprite) {
	if (sprite != NULL) {
		return sprite->sdl_texture;
	}

	return NULL;
}

SDL_Rect getSpriteSdlSrcRect(Sprite* sprite) {
	if (sprite != NULL) {
		return sprite->sdl_srcRect;
	}

	return (SDL_Rect) { 0, 0, 0, 0 };
}

SDL_Rect getSpriteSdlDstRect(Sprite* sprite) {
	if (sprite != NULL) {
		return sprite->sdl_srcRect;
	}

	return (SDL_Rect) { 0, 0, 0, 0 };
}

char* getSpritePath(Sprite* sprite) {
	if (sprite != NULL) {
		return sprite->spritePath;
	}

	return NULL;
}

SDL_RendererFlip getSpriteFlip(Sprite* sprite) {
	if (sprite != NULL) {
		return sprite->flip;
	}

	return 0;
}

float getSpriteAngle(Sprite* sprite) {
	if (sprite != NULL) {
		return sprite->angle;
	}

	return 0.0;
}

SDL_Color getSpriteColorRect(Sprite* sprite) {
	if (sprite != NULL) {
		return sprite->colorRect;
	}

	return (SDL_Color) { 0, 0, 0, 0 };
}

bool isSpriteShowRect(Sprite* sprite) {
	if (sprite != NULL) {
		return sprite->showRect;
	}

	return false;
}

// set procedures
void setSpriteSdlSurface(Sprite** sprite, SDL_Surface* sdl_surface) {
	if (*sprite != NULL) {
		(*sprite)->sdl_surface = sdl_surface;
	}
}

void setSpriteSdlTexture(Sprite** sprite, SDL_Texture* sdl_texture) {
	if (*sprite != NULL) {
		(*sprite)->sdl_texture = sdl_texture;
	}
}

void setSpriteSdlSrcRect(Sprite** sprite, SDL_Rect sdl_rect) {
	if (*sprite != NULL) {
		(*sprite)->sdl_srcRect = sdl_rect;
	}
}

void setSpriteSdlDstRect(Sprite** sprite, SDL_Rect sdl_rect) {
	if (*sprite != NULL) {
		(*sprite)->sdl_dstRect = sdl_rect;
	}
}

void setSpritePath(Sprite** sprite, char* spritePath) {
	if (*sprite != NULL) {
		(*sprite)->spritePath = (char*)malloc(sizeof(char) * (strlen(spritePath) + 1));
		if ((*sprite)->spritePath == NULL) {
			printf("Error! newSprite->spritePath could not initialize!\n");
			return NULL;
		}
		strcpy((*sprite)->spritePath, spritePath);
	}
}

void setSpriteFlip(Sprite** sprite, SDL_RendererFlip flip) {
	if (*sprite != NULL) {
		(*sprite)->flip = flip;
	}
}

void setSpriteRotationAngle(Sprite** sprite, float angle) {
	if (*sprite != NULL) {
		(*sprite)->angle = angle;
	}
}

void setSpriteColorRect(Sprite** sprite, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	if (*sprite != NULL) {
		(*sprite)->colorRect.r = r;
		(*sprite)->colorRect.g = g;
		(*sprite)->colorRect.b = b;
		(*sprite)->colorRect.a = a;
	}
}

void setSpriteShowRect(Sprite** sprite, bool showRect) {
	if (*sprite != NULL) {
		(*sprite)->showRect = showRect;
	}
}