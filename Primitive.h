#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <math.h>
#include <SDL.h>
#include "Window.h"

struct primitive {
	SDL_Rect sdl_rect;
	SDL_Color sdl_color;
	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
	float radius;
};

typedef struct primitive Primitive;

// primitive functions
Primitive* createPrimitive(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void destroyPrimitive(Primitive** primite);
void drawPrimitivePoint(Primitive** primitive, Window** window, float x, float y);
void drawPrimitiveLine(Primitive** primitive, Window** window, float x1, float y1, float x2, float y2);
void drawPrimitiveRect(Primitive** primitive, Window** window, float x, float y, float width, float height);
void drawPrimitiveFillRect(Primitive** primitive, Window** window, float x, float y, float width, float height);
void drawPrimitiveTriangle(Primitive** primitive, Window** window, float x1, float y1, float x2, float y2, float x3, float y3);
void drawPrimitiveFillTriangle(Primitive** primitive, Window** window, float x1, float y1, float x2, float y2, float x3, float y3);
void drawPrimitiveCircle(Primitive** primitive, Window** window, float x, float y, float radius);
void drawPrimitiveFillCircle(Primitive** primitive, Window** window, float x, float y, float radius);

// get primitive functions
SDL_Rect getPrimitiveSdlRect(Primitive* primitive);
SDL_Color getPrimitiveSdlColor(Primitive* primitive);
float getPrimitiveX1(Primitive* primitive);
float getPrimitiveY1(Primitive* primitive);
float getPrimitiveX2(Primitive* primitive);
float getPrimitiveY2(Primitive* primitive);
float getPrimitiveX3(Primitive* primitive);
float getPrimitiveY3(Primitive* primitive);
float getPrimitiveRadius(Primitive* primitive);

// set primitive functions
void setPrimitiveSdlRect(Primitive** primitive, float x, float y, float width, float height);
void setPrimitiveColor(Primitive** primitive, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void setPrimitiveX1(Primitive** primitive, float x1);
void setPrimitiveY1(Primitive** primitive, float y1);
void setPrimitiveX2(Primitive** primitive, float x2);
void setPrimitiveY2(Primitive** primitive, float y2);
void setPrimitiveX3(Primitive** primitive, float x3);
void setPrimitiveY3(Primitive** primitive, float y3);
void setPrimitiveRadius(Primitive** primitive, float radius);

#endif // PRIMITIVE_H