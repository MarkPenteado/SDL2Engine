#include <stdio.h>
#include <stdlib.h>
#include "Primitive.h"

// primitve functions
Primitive* createPrimitive(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	Primitive* newPrimitive = (Primitive*)malloc(sizeof(Primitive));
	if (newPrimitive == NULL) {
		printf("Error! newPrimitive could not initialize!\n");
		return NULL;
	}
	newPrimitive->sdl_rect = (SDL_Rect) { 0, 0, 0, 0 };
	newPrimitive->sdl_color = (SDL_Color) { r, g, b, a };
	newPrimitive->x1 = 0;
	newPrimitive->y1 = 0;
	newPrimitive->x2 = 0;
	newPrimitive->y2 = 0;
	newPrimitive->x3 = 0;
	newPrimitive->y3 = 0;
	newPrimitive->radius = 0.0;

	return newPrimitive;
}

void drawPrimitivePoint(Primitive** primitive, Window** window, float x, float y) {
	if (*primitive) {
		(*primitive)->x1 = x;
		(*primitive)->y1 = y;
		SDL_SetRenderDrawColor((*window)->sdl_renderer, (*primitive)->sdl_color.r, (*primitive)->sdl_color.g, (*primitive)->sdl_color.b, (*primitive)->sdl_color.a);
		SDL_RenderDrawPoint((*window)->sdl_renderer, x, y);
	}
}

void drawPrimitiveLine(Primitive** primitive, Window** window, float x1, float y1, float x2, float y2) {
	if (*primitive) {
		(*primitive)->x1 = x1;
		(*primitive)->y1 = y1;
		(*primitive)->x2 = x2;
		(*primitive)->y1 = y1;
		SDL_SetRenderDrawColor((*window)->sdl_renderer, (*primitive)->sdl_color.r, (*primitive)->sdl_color.g, (*primitive)->sdl_color.b, (*primitive)->sdl_color.a);
		SDL_RenderDrawLine((*window)->sdl_renderer, (*primitive)->x1, (*primitive)->y1, (*primitive)->x2, (*primitive)->y2);
	}
}

void drawPrimitiveRect(Primitive** primitive, Window** window, float x, float y, float width, float height) {
	if (*primitive) {
		(*primitive)->sdl_rect = (SDL_Rect) { x, y, width, height };
		SDL_SetRenderDrawColor((*window)->sdl_renderer, (*primitive)->sdl_color.r, (*primitive)->sdl_color.g, (*primitive)->sdl_color.b, (*primitive)->sdl_color.a);
		SDL_RenderDrawRect((*window)->sdl_renderer, &((*primitive)->sdl_rect));
	}
}

void drawPrimitiveFillRect(Primitive** primitive, Window** window, float x, float y, float width, float height) {
	if (*primitive) {
		(*primitive)->sdl_rect = (SDL_Rect) { x, y, width, height };
		SDL_SetRenderDrawColor((*window)->sdl_renderer, (*primitive)->sdl_color.r, (*primitive)->sdl_color.g, (*primitive)->sdl_color.b, (*primitive)->sdl_color.a);
		SDL_RenderFillRect((*window)->sdl_renderer, &((*primitive)->sdl_rect));
	}
}

/* Draws a triangle
* (x1, y1) its the top vertex
* (x2, y2) its the left vertex
* (x3, y3) its the right vertex */
void drawPrimitiveTriangle(Primitive** primitive, Window** window, float x1, float y1, float x2, float y2, float x3, float y3) {
	if (*primitive) {
		(*primitive)->x1 = x1;
		(*primitive)->y1 = y1;
		(*primitive)->x2 = x2;
		(*primitive)->y2 = y2;
		(*primitive)->x3 = x3;
		(*primitive)->y3 = y3;
		SDL_SetRenderDrawColor((*window)->sdl_renderer, (*primitive)->sdl_color.r, (*primitive)->sdl_color.g, (*primitive)->sdl_color.b, (*primitive)->sdl_color.a);
		SDL_RenderDrawLine((*window)->sdl_renderer, x1, y1, x2, y2);
		SDL_RenderDrawLine((*window)->sdl_renderer, x1, y1, x3, y3);
		SDL_RenderDrawLine((*window)->sdl_renderer, x2, y2, x3, y3);
	}
}

/* Draws a filled triangle
 * (x1, y1) its the top vertex
 * (x2, y2) its the left vertex
 * (x3, y3) its the right vertex */
void drawPrimitiveFillTriangle(Primitive** primitive, Window** window, float x1, float y1, float x2, float y2, float x3, float y3) {
	if (*primitive) {
		(*primitive)->x1 = x1;
		(*primitive)->y1 = y1;
		(*primitive)->x2 = x2;
		(*primitive)->y2 = y2;
		(*primitive)->x3 = x3;
		(*primitive)->y3 = y3;
		SDL_SetRenderDrawColor((*window)->sdl_renderer, (*primitive)->sdl_color.r, (*primitive)->sdl_color.g, (*primitive)->sdl_color.b, (*primitive)->sdl_color.a);
		float invslope1 = ((*primitive)->x2 - (*primitive)->x1) / ((*primitive)->y2 - (*primitive)->y1);
		float invslope2 = ((*primitive)->x3 - (*primitive)->x1) / ((*primitive)->y3 - (*primitive)->y1);

		float curx1 = (*primitive)->x1;
		float curx2 = (*primitive)->x1;

		int scanlineY;
		for (scanlineY = (*primitive)->y1; scanlineY <= (*primitive)->y2; scanlineY++) {
			SDL_RenderDrawLine((*window)->sdl_renderer, (int)curx1, scanlineY, (int)curx2, scanlineY);
			curx1 += invslope1;
			curx2 += invslope2;
		}
	}
}

void drawPrimitiveCircle(Primitive** primitive, Window** window, float x, float y, float radius) {
	if (*primitive) {
		int xC = radius;
		int yC = 0, err = 0;
		(*primitive)->x1 = x;
		(*primitive)->y1 = y;
		(*primitive)->radius = radius;
		SDL_SetRenderDrawColor((*window)->sdl_renderer, (*primitive)->sdl_color.r, (*primitive)->sdl_color.g, (*primitive)->sdl_color.b, (*primitive)->sdl_color.a);
		while (xC >= yC) {
			SDL_RenderDrawPoint((*window)->sdl_renderer, (*primitive)->x1 + xC, (*primitive)->y1 + yC);
			SDL_RenderDrawPoint((*window)->sdl_renderer, (*primitive)->x1 + yC, (*primitive)->y1 + xC);
			SDL_RenderDrawPoint((*window)->sdl_renderer, (*primitive)->x1 - yC, (*primitive)->y1 + xC);
			SDL_RenderDrawPoint((*window)->sdl_renderer, (*primitive)->x1 - xC, (*primitive)->y1 + yC);
			SDL_RenderDrawPoint((*window)->sdl_renderer, (*primitive)->x1 - xC, (*primitive)->y1 - yC);
			SDL_RenderDrawPoint((*window)->sdl_renderer, (*primitive)->x1 - yC, (*primitive)->y1 - xC);
			SDL_RenderDrawPoint((*window)->sdl_renderer, (*primitive)->x1 + yC, (*primitive)->y1 - xC);
			SDL_RenderDrawPoint((*window)->sdl_renderer, (*primitive)->x1 + xC, (*primitive)->y1 - yC);
			yC += 1;
			err += 1 + 2 * yC;
			if (2 * (err - xC) + 1 > 0) {
				xC -= 1;
				err += 1 - 2 * xC;
			}
		}
	}
}

void drawPrimitiveFillCircle(Primitive** primitive, Window** window, float x, float y, float radius) {
	if (*primitive) {
		float cx, cy, cyy, r2 = radius * radius;
		(*primitive)->x1 = x;
		(*primitive)->y1 = y;
		(*primitive)->radius = radius;
		SDL_SetRenderDrawColor((*window)->sdl_renderer, (*primitive)->sdl_color.r, (*primitive)->sdl_color.g, (*primitive)->sdl_color.b, (*primitive)->sdl_color.a);
		for (cy = -radius; cy <= radius; cy++) {
			cx = sqrt(r2 - cy * cy) + 0.5;
			cyy = cy + y;
			SDL_RenderDrawLine((*window)->sdl_renderer, x - cx, cyy, x + cx, cyy);
		}
	}
}

void destroyPrimitive(Primitive** primitive) {
	if (*primitive != NULL) {
		free(*primitive);
		*primitive = NULL;
	}
}

// get primitive functions
SDL_Rect getPrimitiveSdlRect(Primitive* primitive) {
	if (primitive != NULL) {
		return primitive->sdl_rect;
	}

	return (SDL_Rect) { 0, 0, 0, 0 };
}

SDL_Color getPrimitiveSdlColor(Primitive* primitive) {
	if (primitive != NULL) {
		return primitive->sdl_color;
	}

	return (SDL_Color) { 0, 0, 0, 0 };
}

float getPrimitiveX1(Primitive* primitive) {
	if (primitive != NULL) {
		return primitive->x1;
	}

	return -1;
}

float getPrimitiveY1(Primitive* primitive) {
	if (primitive != NULL) {
		return primitive->y1;
	}

	return -1;
}

float getPrimitiveX2(Primitive* primitive) {
	if (primitive != NULL) {
		return primitive->x2;
	}

	return -1;
}

float getPrimitiveY2(Primitive* primitive) {
	if (primitive != NULL) {
		return primitive->y2;
	}

	return -1;
}

float getPrimitiveX3(Primitive* primitive) {
	if (primitive != NULL) {
		return primitive->x3;
	}

	return -1;
}

float getPrimitiveY3(Primitive* primitive) {
	if (primitive != NULL) {
		return primitive->y3;
	}

	return -1;
}

float getPrimitiveRadius(Primitive* primitive) {
	if (primitive != NULL) {
		return primitive->radius;
	}

	return -1;
}

// set primitive functions
void setPrimitiveSdlRect(Primitive** primitive, float x, float y, float width, float height) {
	if (*primitive != NULL) {
		(*primitive)->sdl_rect.x = x;
		(*primitive)->sdl_rect.y = y;
		(*primitive)->sdl_rect.w = width;
		(*primitive)->sdl_rect.h = height;
	}
}

void setPrimitiveColor(Primitive** primitive, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	if (*primitive != NULL) {
		(*primitive)->sdl_color = (SDL_Color) { r, g, b, a };
	}
}

void setPrimitiveX1(Primitive** primitive, float x1) {
	if (*primitive != NULL) {
		(*primitive)->x1 = x1;
	}
}

void setPrimitiveY1(Primitive** primitive, float y1) {
	if (*primitive != NULL) {
		(*primitive)->y1 = y1;
	}
}

void setPrimitiveX2(Primitive** primitive, float x2) {
	if (*primitive != NULL) {
		(*primitive)->x2 = x2;
	}
}

void setPrimitiveY2(Primitive** primitive, float y2) {
	if (*primitive != NULL) {
		(*primitive)->y2 = y2;
	}
}

void setPrimitiveX3(Primitive** primitive, float x3) {
	if (*primitive != NULL) {
		(*primitive)->x3 = x3;
	}
}

void setPrimitiveY3(Primitive** primitive, float y3) {
	if (*primitive != NULL) {
		(*primitive)->y3 = y3;
	}
}

void setPrimitiveRadius(Primitive** primitive, float radius) {
	if (*primitive != NULL) {
		(*primitive)->radius = radius;
	}
}