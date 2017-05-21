#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <SDL.h>
#include "Mouse.h"

struct input {
	SDL_Event* event;
	Mouse* mouse;
};

typedef struct input Input;

// input functions
Input* createInput(SDL_Event* event);
void destroyInput(Input** input);
void setInputMousePosition(Input** input);
bool isInputKeyDown(Input* input, SDL_Keycode sdl_keycode);
bool isInputKeyUp(Input* input, SDL_Keycode sdl_keycode);
bool isInputMouseButtonDown(Input* input, int sdl_button);
bool isInputMouseButtonUp(Input* input, int sdl_button);
bool isInputMouseMotion(Input* input);
bool isInputMouseQuitButton(Input* input);

// get functions
int getInputMouseX(Input* input);
int getInputMouseY(Input* input);
SDL_Event* getInputEvent(Input* input);
Mouse* getInputMouse(Input* input);

// set procedures
void setInputMouseX(Input** input, int x);
void setInputMouseY(Input** input, int y);
void setInputEvent(Input** input, SDL_Event* event);
void setInputMouse(Input** input, Mouse* mouse);

#endif // INPUT_H