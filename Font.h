#ifndef FONT_H
#define FONT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "Window.h"

struct font {
	TTF_Font* ttf_font;
	SDL_Color textColor;
	SDL_Surface* textSurface;
	SDL_Texture* textTexture;
	SDL_Rect renderQuad;
	int textWidth;
	int textHeight;
	char *fontPath;
};

typedef struct font Font;


// font functions
Font* createFont(char* fontPath, int size, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void drawFont(Font** font, Window** window, char* text, int x, int y);
void drawFontWithAlpha(Font** font, Window** window, char* text, int x, int y, Uint8 alpha);
void setFontColor(Font** font, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void setFontSize(Font** font, int size);
void setFontPosition(Font** font, int x, int y);
void destroyFont(Font** font);

// get functions
TTF_Font* getFontTtfFont(Font* font);
SDL_Color getFontTextColor(Font* font);
SDL_Surface* getFontTextSurface(Font* font);
SDL_Texture* getFontTextTexture(Font* font);
SDL_Rect getFontRenderQuad(Font* font);
int getFontTextWidth(Font* font);
int getFontTextHeight(Font* font);
char* getFontPath(Font* font);

// set procedures
void setFontTtfFont(Font** font, TTF_Font* ttf_font);
void setFontTextColor(Font** font, SDL_Color textColor);
void setFontTextSurface(Font** font, SDL_Surface* textSurface);
void setFontTextTexture(Font** font, SDL_Texture* textTexture);
void setFontRenderQuad(Font** font, SDL_Rect renderQuad);
void setFontTextWidth(Font** font, int textWidth);
void setFontTextHeight(Font** font, int textHeight);
void setFontPath(Font** font, char* fontPath);

#endif // FONT_H