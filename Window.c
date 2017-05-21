#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Window.h"

// window functions
Window* createWindow(char* title, int x, int y, int width, int height, Uint32 flags) {
	Window* newWindow = (Window*)malloc(sizeof(Window));
	if (newWindow == NULL) {
		printf("Error! newWindow could not initialize!\n");
		return NULL;
	}
	newWindow->sdl_window = SDL_CreateWindow(title, x, y, width, height, flags);
	if (newWindow->sdl_window == NULL) {
		printf("Error! newWindow->sdl_window could not initialize! SDL_Error: %s\n", SDL_GetError());
		return NULL;
	}
	newWindow->sdl_iconSurface = NULL;
	newWindow->sdl_renderer = NULL;
	return newWindow;
}

int createWindowRenderer(Window** window, int index, Uint32 flags) {
	if (*window != NULL) {
		(*window)->sdl_renderer = SDL_CreateRenderer((*window)->sdl_window, index, flags);
		if ((*window)->sdl_renderer == NULL) {
			printf("Error! newWindow->sdl_renderer could not initialize! SDL_Error: %s\n", SDL_GetError());
			return -1;
		}
		return 1;
	}
}

void windowClear(Window** window) {
	if (*window != NULL) {
		SDL_RenderClear((*window)->sdl_renderer);
	}
}

void windowUpdate(Window** window) {
	if (*window != NULL) {
		SDL_RenderPresent((*window)->sdl_renderer);
	}
}

void setWindowBackground(Window** window, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	if (*window != NULL) {
		SDL_SetRenderDrawColor((*window)->sdl_renderer, r, g, b, a);
	}
}

void setWindowIcon(Window** window, char* iconPath) {
	if (*window != NULL) {
		(*window)->sdl_iconSurface = IMG_Load(iconPath);
		if ((*window)->sdl_iconSurface == NULL) {
			printf("Unable to load image icon %s! SDL_image Error: %s\n", iconPath, IMG_GetError());
			return;
		}
		SDL_SetWindowIcon((*window)->sdl_window, (*window)->sdl_iconSurface);
	}
}

void setWindowFullScreen(Window** window, Uint32 flags) {
	if (*window != NULL) {
		SDL_SetWindowFullscreen((*window)->sdl_window, flags);
	}
}

void destroyWindow(Window** window) {
	if (*window != NULL) {
		if ((*window)->sdl_renderer != NULL) {
			SDL_DestroyRenderer((*window)->sdl_renderer);
			(*window)->sdl_renderer = NULL;
		}
		if ((*window)->sdl_iconSurface != NULL) {
			SDL_FreeSurface((*window)->sdl_iconSurface);
			(*window)->sdl_iconSurface = NULL;
		}
		if ((*window)->sdl_window != NULL) {
			SDL_DestroyWindow((*window)->sdl_window);
			(*window)->sdl_window = NULL;
		}
		free(*window);
		*window = NULL;
	}
}

// get functions
SDL_Window* getSdlWindow(Window* window) {
	if (window != NULL) {
		return window->sdl_window;
	}

	return NULL; // window does not exist
}

const char* getWindowTitle(Window* window) {
	if (window != NULL) {
		return SDL_GetWindowTitle(window->sdl_window);
	}

	return NULL; // window does not exist
}

int getWindowX(Window* window) {
	if (window != NULL) {
		int x, y;
		SDL_GetWindowPosition(window->sdl_window, &x, &y);
		return x;
	}

	return -1; // window does not exist
}

int getWindowY(Window* window) {
	if (window != NULL) {
		int x, y;
		SDL_GetWindowPosition(window->sdl_window, &x, &y);
		return y;
	}

	return -1; // window does not exist
}

int getWindowWidth(Window* window) {
	if (window != NULL) {
		int w, h;
		SDL_GetWindowSize(window->sdl_window, &w, &h);
		return w;
	}

	return -1; // window does not exist
}

int getWindowHeight(Window* window) {
	if (window != NULL) {
		int w, h;
		SDL_GetWindowSize(window->sdl_window, &w, &h);
		return h;
	}

	return -1; // window does not exist
}

Uint32 getWindowFlags(Window* window) {
	if (window != NULL) {
		return SDL_GetWindowFlags(window->sdl_window);
	}

	return -1; // window does not exist
}

SDL_Renderer* getWindowRenderer(Window* window) {
	if (window != NULL) {
		return window->sdl_renderer;
	}

	return NULL;
}

int getWindowBackgroundRedColor(Window* window) {
	if (window != NULL) {
		Uint8 r, g, b, a;
		SDL_GetRenderDrawColor(window->sdl_renderer, &r, &g, &b, &a);
		return r;
	}

	return -1; // window does not exist
}

int getWindowBackgroundGreenColor(Window* window) {
	if (window != NULL) {
		Uint8 r, g, b, a;
		SDL_GetRenderDrawColor(window->sdl_renderer, &r, &g, &b, &a);
		return g;
	}

	return -1; // window does not exist
}

int getWindowBackgroundBlueColor(Window* window) {
	if (window != NULL) {
		Uint8 r, g, b, a;
		SDL_GetRenderDrawColor(window->sdl_renderer, &r, &g, &b, &a);
		return b;
	}

	return -1; // window does not exist
}

int getWindowBackgroundAlphaColor(Window* window) {
	if (window != NULL) {
		Uint8 r, g, b, a;
		SDL_GetRenderDrawColor(window->sdl_renderer, &r, &g, &b, &a);
		return a;
	}

	return -1; // window does not exist
}

SDL_Surface* getWindowIconSurface(Window* window) {
	if (window != NULL) {
		return window->sdl_iconSurface;
	}

	return NULL;
}

// set procedures
void setSdlWindow(Window** window, SDL_Window* sdl_window) {
	if (*window != NULL) {
		(*window)->sdl_window = sdl_window;
	}
}

void setWindowTitle(Window** window, const char* title) {
	if (*window != NULL) {
		SDL_SetWindowTitle((*window)->sdl_window, title);
	}
}

void setWindowX(Window** window, int x) {
	if (window != NULL) {
		int x_, y;
		SDL_GetWindowPosition((*window)->sdl_window, &x_, &y);
		SDL_SetWindowPosition((*window)->sdl_window, x, y);
	}
}

void setWindowY(Window** window, int y) {
	if (window != NULL) {
		int x, y_;
		SDL_GetWindowPosition((*window)->sdl_window, &x, &y_);
		SDL_SetWindowPosition((*window)->sdl_window, x, y);
	}
}

void setWindowWidth(Window** window, int width) {
	if (*window != NULL) {
		int w, h;
		SDL_GetWindowSize((*window)->sdl_window, &w, &h);
		SDL_SetWindowSize((*window)->sdl_window, width, h);
	}
}

void setWindowHeight(Window** window, int height) {
	if (*window != NULL) {
		int w, h;
		SDL_GetWindowSize((*window)->sdl_window, &w, &h);
		SDL_SetWindowSize((*window)->sdl_window, w, height);
	}
}

void setWindowRenderer(Window** window, SDL_Renderer* renderer) {
	if (*window != NULL) {
		(*window)->sdl_renderer = renderer;
	}
}

void setWindowSurfaceIcon(Window** window, SDL_Surface* surface) {
	if (*window != NULL) {
		(*window)->sdl_iconSurface = surface;
	}
}