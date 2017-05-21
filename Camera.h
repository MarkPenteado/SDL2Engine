#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>

struct camera {
	int x;
	int y;
};

typedef struct camera Camera;

// Camera functions
Camera* createCamera(int x, int y);
void destroyCamera(Camera** camera);

// get functions
int getCameraX(Camera* camera);
int getCameraY(Camera* camera);

// set procedures
void setCameraX(Camera** camera, int x);
void setCameraY(Camera** camera, int y);

#endif // CAMERA_H