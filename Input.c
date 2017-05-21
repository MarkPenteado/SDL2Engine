#include <stdio.h>
#include <stdlib.h>
#include "Input.h"

// input functions
Input* createInput(SDL_Event* event) {
	Input* newInput = (Input*)malloc(sizeof(Input));
	if (newInput == NULL) {
		printf("Error! newInput could not initialize!\n");
		return NULL;
	}
	newInput->event = event;
	newInput->mouse = createMouse();
	if (newInput->mouse == NULL) {
		return NULL;
	}
	return newInput;
}

void destroyInput(Input** input) {
	if (*input != NULL) {
		if ((*input)->event != NULL) {
			(*input)->event = NULL;
		}
		if ((*input)->mouse != NULL) {
			destroyMouse(&((*input)->mouse));
			(*input)->mouse = NULL;
		}
		free(*input);
		*input = NULL;
	}
}

void setInputMousePosition(Input** input) {
	if (*input != NULL) {
		SDL_GetMouseState(&((*input)->mouse->x), &((*input)->mouse->y));
	}
}

bool isInputKeyDown(Input* input, SDL_Keycode sdl_keycode) {
	if (input != NULL) {
		if (input->event->type == SDL_KEYDOWN && input->event->key.keysym.sym == sdl_keycode) {
			return true;
		}
	}
	return false;
}

bool isInputKeyUp(Input* input, SDL_Keycode sdl_keycode) {
	if (input != NULL) {
		if (input->event->type == SDL_KEYUP && input->event->key.keysym.sym == sdl_keycode) {
			return true;
		}
	}
	return false;
}

bool isInputMouseButtonDown(Input* input, int sdl_button) {
	if (input != NULL) {
		if (input->event->type == SDL_MOUSEBUTTONDOWN && input->event->button.button == sdl_button) {
			return true;
		}
	}
	return false;
}

bool isInputMouseButtonUp(Input* input, int sdl_button) {
	if (input != NULL) {
		if (input->event->type == SDL_MOUSEBUTTONUP && input->event->button.button == sdl_button) {
			return true;
		}
	}
	return false;
}

bool isInputMouseMotion(Input* input) {
	if (input != NULL) {
		if (input->event->type == SDL_MOUSEMOTION) {
			return true;
		}
	}
	return false;
}

bool isInputMouseQuitButton(Input* input) {
	if (input != NULL) {
		if (input->event->type == SDL_QUIT) {
			return true;
		}
	}
	return false;
}

// get functions
int getInputMouseX(Input* input) {
	if (input != NULL) {
		return getMouseX(input->mouse);
	}

	return -1;
}

int getInputMouseY(Input* input) {
	if (input != NULL) {
		return getMouseY(input->mouse);
	}

	return -1;
}

SDL_Event* getInputEvent(Input* input) {
	if (input != NULL) {
		return input->event;
	}

	return NULL;
}

Mouse* getInputMouse(Input* input) {
	if (input != NULL) {
		return input->mouse;
	}

	return NULL;
}

// set procedures
void setInputMouseX(Input** input, int x) {
	if (*input != NULL) {
		setMouseX(&((*input)->mouse), x);
	}
}

void setInputMouseY(Input** input, int y) {
	if (*input != NULL) {
		setMouseY(&((*input)->mouse), y);
	}
}

void setInputEvent(Input** input, SDL_Event* event) {
	if (*input != NULL) {
		(*input)->event = event;
	}
}

void setInputMouse(Input** input, Mouse* mouse) {
	if (*input != NULL) {
		(*input)->mouse = mouse;
	}
}