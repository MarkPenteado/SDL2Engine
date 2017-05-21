#ifndef SPRITE_H
#define SPRITE_H

#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Window.h"

struct sprite {
	SDL_Surface* sdl_surface;
	SDL_Texture* sdl_texture;
	SDL_Rect sdl_srcRect;
	SDL_Rect sdl_dstRect;
	SDL_RendererFlip flip;
	char* spritePath;
	float angle;
	SDL_Color colorRect;
	bool showRect;
};

typedef struct sprite Sprite;

// Sprite functions
Sprite* createSprite(Window** window, char* spritePath, int width, int height);
void destroySprite(Sprite** sprite);
void drawSpriteFull(Window** window, Sprite** sprite, int x, int y);
void drawSprite(Window** window, Sprite** sprite, int spriteX, int spriteY, int spriteWidth, int spriteHeight, int drawX, int drawY, int drawWidth, int drawHeight);

// get functions
SDL_Surface* getSpriteSdlSurface(Sprite* sprite);
SDL_Texture* getSpriteSdlTexture(Sprite* sprite);
SDL_Rect getSpriteSdlSrcRect(Sprite* sprite);
SDL_Rect getSpriteSdlDstRect(Sprite* sprite);
char* getSpritePath(Sprite* sprite);
SDL_RendererFlip getSpriteFlip(Sprite* sprite);
float getSpriteAngle(Sprite* sprite);
SDL_Color getSpriteColorRect(Sprite* sprite);
bool isSpriteShowRect(Sprite* sprite);

// set procedures
void setSpriteSdlSurface(Sprite** sprite, SDL_Surface* sdl_surface);
void setSpriteSdlTexture(Sprite** sprite, SDL_Texture* sdl_texture);
void setSpriteSdlSrcRect(Sprite** sprite, SDL_Rect sdl_rect);
void setSpriteSdlDstRect(Sprite** sprite, SDL_Rect sdl_rect);
void setSpritePath(Sprite** sprite, char* spritePath);
void setSpriteFlip(Sprite** sprite, SDL_RendererFlip flip);
void setSpriteRotationAngle(Sprite** sprite, float angle);
void setSpriteColorRect(Sprite** sprite, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void setSpriteShowRect(Sprite** sprite, bool showRect);

#endif // SPRITE_H