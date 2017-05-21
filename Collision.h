#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include <SDL.h>
#include "Primitive.h"

struct collision {
	Primitive* primitiveA;
	Primitive* primitiveB;
	bool collisionCheck;
};

typedef struct collision Collision;

// collision functions
Collision* createCollision(void);
void destroyCollision(Collision** collision);
bool checkCollisionRectangular(Collision** collision, Primitive* primitiveA, Primitive* primitiveB);
bool checkCollisionCircular(Collision** collision, Primitive* primitiveA, Primitive* primitiveB);

// get functions
Primitive* getCollisionPrimitiveA(Collision* collision);
Primitive* getCollisionPrimitiveB(Collision* collision);
bool isCollisionCheck(Collision* collision);

// set procedures
void setCollisionPrimitiveA(Collision** collision, Primitive* primitive1);
void setCollisionPrimitiveB(Collision** collision, Primitive* primitive2);
void setCollisionCheck(Collision** collision, bool collisionCheck);

#endif // COLLISION_H