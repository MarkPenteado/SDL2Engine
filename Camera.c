#include <stdio.h>
#include <stdlib.h>
#include "Camera.h"

// Camera functions
Camera* createCamera(int x, int y) {
	Camera* newCamera = (Camera*)malloc(sizeof(Camera));
	if (newCamera == NULL) {
		printf("Error! newCamera could not initialize!\n");
		return NULL;
	}
	newCamera->x = x;
	newCamera->y = y;
	return newCamera;
}

void destroyCamera(Camera** camera) {
	if (*camera != NULL) {
		free(*camera);
		*camera = NULL;
	}
}

// get functions
int getCameraX(Camera* camera) {
	if (camera != NULL) {
		return camera->x;
	}

	return -1;
}

int getCameraY(Camera* camera) {
	if (camera != NULL) {
		return camera->y;
	}

	return -1;
}

// set procedures
void setCameraX(Camera** camera, int x) {
	if (*camera != NULL) {
		(*camera)->x = x;
	}
}

void setCameraY(Camera** camera, int y) {
	if (*camera != NULL) {
		(*camera)->y = y;
	}
}