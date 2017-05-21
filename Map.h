#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include <SDL.h>
#include "Sprite.h"
#include "Window.h"

struct map {
	Sprite* sprite;
	SDL_Rect* srcRect;
	SDL_Rect dstRect;
	int** tileMap;
	char* mapPath;
	int tiles;
	int sizeTileMapX;
	int sizeTileMapY;
	int ignoredIndex;
};

typedef struct map Map;

// Map functions
Map* createMap(char* mapPath, Sprite* sprite, int ignoredIndex);
void destroyMap(Map** map);
int addMapTile(Map** map, int x, int y, int width, int height);
void drawMapOnIndex(Window** window, Map** map, int index, int x, int y, int dstWidth, int dstHeight);
int drawMap(Window** window, Map** map, int x, int y, int dstWidth, int dstHeight);

// get functions
Sprite* getMapSprite(Map* map);
SDL_Rect* getMapSrcRect(Map* map);
SDL_Rect getMapDstRect(Map* map);
int** getTileMap(Map* map);
char* getMapPath(Map* map);
int getMapTiles(Map* map);
int getMapSizeTileMapX(Map* map);
int getMapSizeTileMapY(Map* map);
int getMapIgnoredIndex(Map* map);

// set procedures
void setMapSprite(Map** map, Sprite* sprite);
void setMapSrcRect(Map** map, SDL_Rect* srcRect);
void setMapDstRect(Map** map, SDL_Rect dstRect);
void setTileMap(Map** map, int** tileMap);
void setMapPath(Map** map, char* mapPath);
void setMapTiles(Map** map, int tiles);
void setMapSizeTileMapX(Map** map, int sizeTileMapX);
void setMapSizeTileMapY(Map** map, int sizeTileMapY);
void setMapIgnoredIndex(Map** map, int ignoredIndex);

#endif // MAP_H