#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Collision.h"

// collision functions
Collision* createCollision(void) {
	Collision* newCollision = (Collision*)malloc(sizeof(Collision));
	if (newCollision == NULL) {
		printf("Error! newCollision could not initialize!\n");
		return NULL;
	}
	newCollision->primitiveA = NULL;
	newCollision->primitiveB = NULL;
	newCollision->collisionCheck = false;
}

void destroyCollision(Collision** collision) {
	if (*collision != NULL) {
		(*collision)->primitiveA = NULL;
		(*collision)->primitiveB = NULL;
		free(*collision);
		*collision = NULL;
	}
}

bool checkCollisionRectangular(Collision** collision, Primitive* primitiveA, Primitive* primitiveB) {
	if (*collision != NULL) {
		(*collision)->primitiveA = primitiveA;
		(*collision)->primitiveB = primitiveB;
		if (primitiveA->sdl_rect.x < primitiveB->sdl_rect.x + primitiveB->sdl_rect.w &&
			primitiveA->sdl_rect.x + primitiveA->sdl_rect.w > primitiveB->sdl_rect.x &&
			primitiveA->sdl_rect.y < primitiveB->sdl_rect.y + primitiveB->sdl_rect.h &&
			primitiveA->sdl_rect.h + primitiveA->sdl_rect.y > primitiveB->sdl_rect.y) {
			(*collision)->collisionCheck = true;
			return true;
		} else {
			(*collision)->collisionCheck = false;
			return false;
		}
	}
	return false;
}

bool checkCollisionCircular(Collision** collision, Primitive* primitiveA, Primitive* primitiveB) {
	if (*collision != NULL) {
		(*collision)->primitiveA = primitiveA;
		(*collision)->primitiveB = primitiveB;
		
		int dx = primitiveA->x1 - primitiveB->x1;
		int dy = primitiveA->y1 - primitiveB->y1;
		float distance = sqrt(dx * dx + dy * dy);

		if (distance < primitiveA->radius + primitiveA->radius) {
			(*collision)->collisionCheck = true;
			return true;
		} else {
			(*collision)->collisionCheck = false;
			return false;
		}
	}
	return false;
}

// get functions
Primitive* getCollisionPrimitiveA(Collision* collision) {
	if (collision != NULL) {
		return collision->primitiveA;
	}

	return NULL;
}

Primitive* getCollisionPrimitiveB(Collision* collision) {
	if (collision != NULL) {
		return collision->primitiveB;
	}

	return NULL;
}

bool isCollisionCheck(Collision* collision) {
	if (collision != NULL) {
		return collision->collisionCheck;
	}

	return false;
}

// set procedures
void setCollisionPrimitiveA(Collision** collision, Primitive* primitiveA) {
	if (*collision != NULL) {
		(*collision)->primitiveA = primitiveA;
	}
}

void setCollisionPrimitiveB(Collision** collision, Primitive* primitiveB) {
	if (*collision != NULL) {
		(*collision)->primitiveB = primitiveB;
	}
}

void setCollisionCheck(Collision** collision, bool collisionCheck) {
	if (*collision != NULL) {
		(*collision)->collisionCheck = collisionCheck;
	}
}