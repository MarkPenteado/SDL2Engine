#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <SDL_image.h>

struct window {
	SDL_Window* sdl_window;
	SDL_Renderer* sdl_renderer;
	SDL_Surface* sdl_iconSurface;
};

typedef struct window Window;

// window functions
Window* createWindow(char* title, int x, int y, int width, int height, Uint32 flags);
int createWindowRenderer(Window** window, int index, Uint32 flags); // SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
void windowClear(Window** window);
void windowUpdate(Window** window);
void setWindowBackground(Window** window, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void setWindowIcon(Window** window, char* iconPath);
void setWindowFullScreen(Window** window, Uint32 flags); // SDL_WINDOW_FULLSCREEN, SDL_WINDOW_FULLSCREEN_DESKTOP or 0
void destroyWindow(Window** window);

// get functions
SDL_Window* getSdlWindow(Window* window);
const char* getWindowTitle(Window* window);
int getWindowX(Window* window);
int getWindowY(Window* window);
int getWindowWidth(Window* window);
int getWindowHeight(Window* window);
Uint32 getWindowFlags(Window* window);
SDL_Renderer* getWindowRenderer(Window* window);
int getWindowBackgroundRedColor(Window* window);
int getWindowBackgroundGreenColor(Window* window);
int getWindowBackgroundBlueColor(Window* window);
int getWindowBackgroundAlphaColor(Window* window);
SDL_Surface* getWindowIconSurface(Window* window);

// set procedures
void setSdlWindow(Window** window, SDL_Window* sdl_window);
void setWindowTitle(Window** window, const char* title);
void setWindowX(Window** window, int x);
void setWindowY(Window** window, int y);
void setWindowWidth(Window** window, int width);
void setWindowHeight(Window** window, int height);
void setWindowRenderer(Window** window, SDL_Renderer* renderer);
void setWindowSurfaceIcon(Window** window, SDL_Surface* surface);

#endif // WINDOW_H