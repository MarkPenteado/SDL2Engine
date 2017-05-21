#ifndef SOUND_H
#define SOUND_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdbool.h>

struct sound {
	Mix_Music* music;
	Mix_Chunk* chunk;
	char *soundPath;
	bool loop;
	int volume;
};

typedef struct sound Sound;

// sound functions
Sound* createSoundMusic(char* soundPath, bool loop, int volume);
Sound* createSoundChunk(char* soundPath, bool loop, int volume);
void destroySound(Sound** sound);
int playSoundMusic(Sound* sound);
int playSoundChunk(Sound* sound);
void pauseSoundMusic(Sound* sound);
void resumeSoundMusic(Sound* sound);
void rewindSoundMusic(Sound* sound);
void haltSoundMusic(Sound* sound);
bool isSoundMusicPlaying(Sound* sound);
bool isSoundMusicPaused(Sound* sound);

// get functions
Mix_Music* getSoundMusic(Sound* sound);
Mix_Chunk* getSoundChunk(Sound* sound);
char* getSoundPath(Sound* sound);
bool isSoundLoop(Sound* sound);
int getSoundVolume(Sound* sound);

// set proceures
void setSoundMusic(Sound** sound, Mix_Music* mixMusic);
void setSoundChunk(Sound** sound, Mix_Chunk* mixChunk);
void setSoundPath(Sound** sound, char* soundPath);
void setSoundLoop(Sound** sound, bool loop);
void setSoundVolumeMusic(Sound** sound, int volume);
void setSoundVolumeChunk(Sound** sound, int volume);

#endif // SOUND_H