#include <stdio.h>
#include <stdlib.h>
#include "Mouse.h"

// mouse functions
Mouse* createMouse(void) {
	Mouse* newMouse = (Mouse*)malloc(sizeof(Mouse));
	if (newMouse == NULL) {
		printf("Error! newMouse could not initialize!\n");
		return NULL;
	}
	newMouse->x = 0;
	newMouse->y = 0;
}

void destroyMouse(Mouse** mouse) {
	if (*mouse != NULL) {
		free(*mouse);
		*mouse = NULL;
	}
}

void setMouseShow(Mouse* mouse) {
	if (mouse != NULL) {
		SDL_ShowCursor(1);
	}
}

void setMouseHide(Mouse* mouse) {
	if (mouse != NULL) {
		SDL_ShowCursor(0);
	}
}

// get functions
int getMouseX(Mouse* mouse) {
	if (mouse != NULL) {
		return mouse->x;
	}

	return -1;
}

int getMouseY(Mouse* mouse) {
	if (mouse != NULL) {
		return mouse->y;
	}

	return -1;
}

// set procedures
void setMouseX(Mouse** mouse, int x) {
	if (*mouse != NULL) {
		return (*mouse)->x = x;
	}

	return -1;
}

void setMouseY(Mouse** mouse, int y) {
	if (*mouse != NULL) {
		return (*mouse)->y = y;
	}

	return -1;
}