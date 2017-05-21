#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sound.h"

Sound* createSoundMusic(char* soundPath, bool loop, int volume) {
	Sound* newSound = (Sound*)malloc(sizeof(Sound));
	if (newSound == NULL) {
		printf("Error! newSound could not initialize!\n");
		return NULL;
	}
	newSound->music = Mix_LoadMUS(soundPath);
	if (newSound->music == NULL) {
		printf("Music: %s dont found!\n", soundPath);
		return NULL;
	}
	newSound->chunk = NULL;
	newSound->soundPath = (char*)malloc(sizeof(char*) * (strlen(soundPath) + 1));
	if (newSound->soundPath == NULL) {
		printf("Error! newSound->soundPath could not initialize!\n");
		return NULL;
	}
	strcpy(newSound->soundPath, soundPath);
	newSound->loop = loop;
	newSound->volume = volume;

	return newSound;
}

Sound* createSoundChunk(char* soundPath, bool loop, int volume) {
	Sound* newSound = (Sound*)malloc(sizeof(Sound));
	if (newSound == NULL) {
		printf("Error! newSound could not initialize!\n");
		return NULL;
	}
	newSound->chunk = Mix_LoadWAV(soundPath);
	if (newSound->chunk == NULL) {
		printf("Effect: %s dont found!\n", soundPath);
		return NULL;
	}
	newSound->music = NULL;
	newSound->soundPath = (char*)malloc(sizeof(char*) * (strlen(soundPath) + 1));
	if (newSound->soundPath == NULL) {
		printf("Error! newSound->soundPath could not initialize!\n");
		return NULL;
	}
	strcpy(newSound->soundPath, soundPath);
	newSound->loop = loop;
	newSound->volume = volume;

	return newSound;
}

void destroySound(Sound** sound) {
	if (*sound != NULL) {
		if ((*sound)->music != NULL) {
			Mix_FreeMusic((*sound)->music);
			(*sound)->music = NULL;
		}
		if ((*sound)->chunk != NULL) {
			Mix_FreeChunk((*sound)->chunk);
			(*sound)->chunk = NULL;
		}
		if ((*sound)->soundPath != NULL) {
			free((*sound)->soundPath);
			(*sound)->soundPath = NULL;
		}
		free(*sound);
		*sound = NULL;
	}
}

int playSoundMusic(Sound* sound) {
	if (sound != NULL) {
		Mix_VolumeMusic(sound->volume);
		if (Mix_PlayingMusic() == 0) {
			if (sound->loop) {
				if (Mix_PlayMusic(sound->music, -1) < 0) {
					printf("Mix_Error: %s\n", Mix_GetError());
					return -1;
				}
			} else {
				if (Mix_PlayMusic(sound->music, 0) < 0) {
					printf("Mix_Error: %s\n", Mix_GetError());
					return -1;
				}
			}
			return 1;
		}
		return 1;
	}
	return -1;
}

int playSoundChunk(Sound* sound) {
	if (sound != NULL) {
		Mix_VolumeChunk(sound->chunk, sound->volume);
		if (Mix_Playing(-1) == 0) { // Remove Mix_Error: No free channels available
			if (sound->loop) {
				if (Mix_PlayChannel(-1, sound->chunk, -1) < 0) {
					printf("Mix_Error: %s\n", Mix_GetError());
					return -1;
				}
				return 1;
			} else {
				if (Mix_PlayChannel(-1, sound->chunk, 0) < 0) {
					printf("Mix_Error: %s\n", Mix_GetError());
					return -1;
				}
				return 1;
			}
		}
		return 1;
	}
	return -1;
}

void pauseSoundMusic(Sound* sound) {
	if (sound != NULL) {
		Mix_PauseMusic();
	}
}

void resumeSoundMusic(Sound* sound) {
	if (sound != NULL) {
		Mix_ResumeMusic();
	}
}

void rewindSoundMusic(Sound* sound) {
	if (sound != NULL) {
		Mix_RewindMusic();
	}
}

void haltSoundMusic(Sound* sound) {
	if (sound != NULL) {
		Mix_HaltMusic();
	}
}

bool isSoundMusicPlaying(Sound* sound) {
	if (sound != NULL) {
		return Mix_PlayingMusic() ? true : false;
	}

	return false;
}
bool isSoundMusicPaused(Sound* sound) {
	if (sound != NULL) {
		return Mix_PausedMusic() ? true : false;
	}

	return false;
}

// get functions
Mix_Music* getSoundMusic(Sound* sound) {
	if (sound != NULL) {
		return sound->music;
	}

	return NULL;
}

Mix_Chunk* getSoundChunk(Sound* sound) {
	if (sound != NULL) {
		return sound->chunk;
	}

	return NULL;
}

char* getSoundPath(Sound* sound) {
	if (sound != NULL) {
		return sound->soundPath;
	}

	return NULL;
}

bool isSoundLoop(Sound* sound) {
	if (sound != NULL) {
		return sound->loop;
	}

	return false;
}

int getSoundVolume(Sound* sound) {
	if (sound != NULL) {
		return sound->volume;
	}

	return -1;
}

// set proceures
void setSoundMusic(Sound** sound, Mix_Music* mixMusic) {
	if (*sound != NULL) {
		(*sound)->music = mixMusic;
	}
}

void setSoundChunk(Sound** sound, Mix_Chunk* mixChunk) {
	if (*sound != NULL) {
		(*sound)->chunk = mixChunk;
	}
}

void setSoundPath(Sound** sound, char* soundPath) {
	if (*sound != NULL) {
		(*sound)->soundPath = (char*)malloc(sizeof(char*) * (strlen(soundPath) + 1));
		if ((*sound)->soundPath == NULL) {
			printf("Error! newSound->soundPath could not initialize!\n");
			return NULL;
		}
		strcpy((*sound)->soundPath, soundPath);
	}
}

void setSoundLoop(Sound** sound, bool loop) {
	if (*sound != NULL) {
		(*sound)->loop = loop;
	}
}

void setSoundVolumeMusic(Sound** sound, int volume) {
	if (*sound != NULL) {
		(*sound)->volume = volume;
		Mix_VolumeMusic(volume);
	}
}

void setSoundVolumeChunk(Sound** sound, int volume) {
	if (*sound != NULL) {
		(*sound)->volume = volume;
		Mix_VolumeChunk((*sound)->chunk, volume);
	}
}