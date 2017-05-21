#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Font.h"

Font* createFont(char* fontPath, int size, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	Font* newFont = (Font*)malloc(sizeof(Font));
	if (newFont == NULL) {
		printf("Error! newFont could not initialize!\n");
		return NULL;
	}
	newFont->ttf_font = TTF_OpenFont(fontPath, size);
	if (newFont->ttf_font == NULL) {
		printf("Unable to load the font %s! SDL_ttf Error: %s\n", fontPath, TTF_GetError());
		return NULL;
	}
	newFont->textColor = (SDL_Color) { r, g, b, a };
	newFont->textSurface = NULL;
	newFont->textTexture = NULL;
	newFont->renderQuad = (SDL_Rect) { 0, 0, 0, 0 };
	newFont->textWidth = 0;
	newFont->textHeight = 0;
	newFont->fontPath = (char*)malloc(sizeof(char) * (strlen(fontPath) + 1));
	if (newFont->fontPath == NULL) {
		printf("Error! newFont->fontPath could not initialize!\n");
		return NULL;
	}
	strcpy(newFont->fontPath, fontPath);
	return newFont;
}

void drawFont(Font** font, Window** window, char* text, int x, int y) {
	if (*font != NULL) {
		(*font)->textSurface = TTF_RenderText_Solid((*font)->ttf_font, text, (*font)->textColor);
		(*font)->textTexture = SDL_CreateTextureFromSurface((*window)->sdl_renderer, (*font)->textSurface);
		(*font)->textWidth = (*font)->textSurface->w;
		(*font)->textHeight = (*font)->textSurface->h;
		SDL_FreeSurface((*font)->textSurface);
		(*font)->textSurface = NULL;
		(*font)->renderQuad = (SDL_Rect) { x, y, (*font)->textWidth, (*font)->textHeight };
		SDL_RenderCopy((*window)->sdl_renderer, (*font)->textTexture, NULL, &((*font)->renderQuad));
		SDL_DestroyTexture((*font)->textTexture);
		(*font)->textTexture = NULL;
	}
}

void drawFontWithAlpha(Font** font, Window** window, char* text, int x, int y, Uint8 alpha) {
	if (*font != NULL) {
		(*font)->textSurface = TTF_RenderText_Solid((*font)->ttf_font, text, (*font)->textColor);
		(*font)->textTexture = SDL_CreateTextureFromSurface((*window)->sdl_renderer, (*font)->textSurface);
		(*font)->textWidth = (*font)->textSurface->w;
		(*font)->textHeight = (*font)->textSurface->h;
		SDL_FreeSurface((*font)->textSurface);
		(*font)->textSurface = NULL;
		(*font)->renderQuad = (SDL_Rect) { x, y, (*font)->textWidth, (*font)->textHeight };
		SDL_SetTextureAlphaMod((*font)->textTexture, alpha);
		SDL_RenderCopy((*window)->sdl_renderer, (*font)->textTexture, NULL, &((*font)->renderQuad));
		SDL_DestroyTexture((*font)->textTexture);
		(*font)->textTexture = NULL;
	}
}

void setFontColor(Font** font, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	if (*font != NULL) {
		(*font)->textColor = (SDL_Color) { r, g, b, a };
	}
}

void setFontSize(Font** font, int size) {
	if (*font != NULL) {
		TTF_Font* newFont = TTF_OpenFont((*font)->fontPath, size);
		if (newFont == NULL) {
			printf("Unable to load the font %s! SDL_ttf Error: %s\n", (*font)->fontPath, TTF_GetError());
			return NULL;
		}
		if ((*font)->ttf_font != NULL) { TTF_CloseFont((*font)->ttf_font); (*font)->ttf_font = NULL; }
		(*font)->ttf_font = newFont;
	}
}

void setFontPosition(Font** font, int x, int y) {
	if (*font != NULL) {
		(*font)->renderQuad = (SDL_Rect) { x, y, (*font)->textWidth, (*font)->textHeight };
	}
}

void destroyFont(Font** font) {
	if (*font != NULL) {
		if ((*font)->textSurface != NULL) { SDL_FreeSurface((*font)->textSurface); (*font)->textSurface = NULL;  }
		if ((*font)->textTexture != NULL) { SDL_DestroyTexture((*font)->textTexture); (*font)->textTexture = NULL; }
		if ((*font)->ttf_font != NULL) { TTF_CloseFont((*font)->ttf_font); (*font)->ttf_font = NULL; }
		if ((*font)->fontPath != NULL) { free((*font)->fontPath); (*font)->fontPath = NULL; }
		free(*font);
		*font = NULL;
	}
}

// get functions
TTF_Font* getFontTtfFont(Font* font) {
	if (font != NULL) {
		return font->ttf_font;
	}

	return NULL;
}

SDL_Color getFontTextColor(Font* font) {
	if (font != NULL) {
		return font->textColor;
	}

	return (SDL_Color) {0, 0, 0, 0};
}

SDL_Surface* getFontTextSurface(Font* font) {
	if (font != NULL) {
		return font->textSurface;
	}

	return NULL;
}

SDL_Texture* getFontTextTexture(Font* font) {
	if (font != NULL) {
		return font->textTexture;
	}

	return NULL;
}

SDL_Rect getFontRenderQuad(Font* font) {
	if (font != NULL) {
		return font->renderQuad;
	}

	return (SDL_Rect) {0, 0, 0, 0};
}

int getFontTextWidth(Font* font) {
	if (font != NULL) {
		return font->textWidth;
	}

	return -1;
}

int getFontTextHeight(Font* font) {
	if (font != NULL) {
		return font->textHeight;
	}

	return -1;
}

char* getFontPath(Font* font) {
	if (font != NULL) {
		return font->fontPath;
	}

	return NULL;
}

// set procedures
void setFontTtfFont(Font** font, TTF_Font* ttf_font) {
	if (*font != NULL) {
		(*font)->ttf_font = ttf_font;
	}
}

void setFontTextColor(Font** font, SDL_Color textColor) {
	if (*font != NULL) {
		(*font)->textColor = textColor;
	}
}

void setFontTextSurface(Font** font, SDL_Surface* textSurface) {
	if (*font != NULL) {
		(*font)->textSurface = textSurface;
	}
}

void setFontTextTexture(Font** font, SDL_Texture* textTexture) {
	if (*font != NULL) {
		(*font)->textTexture = textTexture;
	}
}

void setFontRenderQuad(Font** font, SDL_Rect renderQuad) {
	if (*font != NULL) {
		(*font)->renderQuad = renderQuad;
	}
}

void setFontTextWidth(Font** font, int textWidth) {
	if (*font != NULL) {
		(*font)->textWidth = textWidth;
	}
}

void setFontTextHeight(Font** font, int textHeight) {
	if (*font != NULL) {
		(*font)->textHeight = textHeight;
	}
}

void setFontPath(Font** font, char* fontPath) {
	if (*font != NULL) {
		(*font)->fontPath = (char*)malloc(sizeof(char) * (strlen(fontPath) + 1));
		if ((*font)->fontPath == NULL) {
			printf("Error! (*font)->fontPath could not initialize!\n");
			return NULL;
		}
		strcpy((*font)->fontPath, fontPath);
	}
}