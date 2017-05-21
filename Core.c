#include "Core.h"

int initCore(void) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return -1;
	}

	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		printf("SDL_mixer could not initialize! SDL Error: %s\n", SDL_GetError());
		return -1;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		printf("Mix could not initialize! Mix Error: %s\n", Mix_GetError());
		return -1;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return -1;
	}

	if (TTF_Init() < 0) {
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return -1;
	}
}

void quitCore(void) {
	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();
}