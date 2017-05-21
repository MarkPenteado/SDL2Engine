#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"

// prototypes of extra functions and procedures
int** createMatrix(int rows, int columns);
void loadMapFile(FILE** file, Map** map);

//Map functions
Map* createMap(char* mapPath, Sprite* sprite, int ignoredIndex) {
	Map* newMap = (Map*)malloc(sizeof(Map));
	if (newMap == NULL) {
		printf("Error! newMap could not initialize!\n");
		return NULL;
	}
	newMap->sprite = sprite;
	newMap->srcRect = NULL;
	newMap->dstRect = (SDL_Rect){ 0, 0, 0, 0 };
	newMap->tiles = 0;
	newMap->ignoredIndex = ignoredIndex;
	newMap->mapPath = (char*)malloc(sizeof(char) * (strlen(mapPath) + 1));
	if (newMap->mapPath == NULL) {
		printf("Error! newMap->mapPath could not initialize!\n");
		return NULL;
	}
	strcpy(newMap->mapPath, mapPath);
	FILE* fileMapPath = fopen(newMap->mapPath, "r");
	if (fileMapPath == NULL) {
		printf("Error! The file: %s does not exist!\n", newMap->mapPath);
		return NULL;
	}
	fscanf(fileMapPath, "%d", &(newMap->sizeTileMapX));
	fscanf(fileMapPath, "%d", &(newMap->sizeTileMapY));
	newMap->tileMap = createMatrix(newMap->sizeTileMapX, newMap->sizeTileMapY);
	loadMapFile(&fileMapPath, &newMap);
	if (fileMapPath != NULL) {
		fclose(fileMapPath);
	}
	return newMap;
}

// create the map array
int** createMatrix(int rows, int columns) {
	int i;
	int** matrix = (int**)malloc(sizeof(int*) * rows);
	if (matrix == NULL) {
		printf("Error! matrix could not initialize!\n");
		return NULL;
	}
	for (i = 0; i < rows; i++) {
		matrix[i] = (int*)malloc(sizeof(int) * columns);
		if (matrix[i] == NULL) {
			printf("Error! matrix[%d] could not initialize!\n", i);
			return NULL;
		}
	}
	return matrix;
}

/* Map File Format:
* x <- Number of The Rows
* y <- Number of the Columns
* 0 1 0 0 1 <- each number represent one tile
* 0 1 2 0 1 <- you need space to separate the tiles
* 0 0 0 0 5 <- each tile is a index in the SDL_Rect of Map* map
*/
void loadMapFile(FILE** file, Map** map) {
	char c;
	int i = 0, j = 0;
	while ((c = getc(*file)) != EOF) {
		if (c != ' ' && c != '\n') {
			(*map)->tileMap[i][j] = (int)(c - '0');
			if (i < (*map)->sizeTileMapX) {
				if (j < ((*map)->sizeTileMapY - 1)) {
					j++;
				} else {
					j = 0;
					i++;
				}
			}
		}
	}
}

void destroyMap(Map** map) {
	if (*map != NULL) {
		if ((*map)->sprite != NULL) {
			(*map)->sprite = NULL;
		}
		if ((*map)->srcRect != NULL) {
			free((*map)->srcRect);
			(*map)->srcRect = NULL;
		}
		if ((*map)->mapPath != NULL) {
			free((*map)->mapPath);
			(*map)->mapPath = NULL;
		}
		if ((*map)->tileMap != NULL) {
			int i;
			for (i = (*map)->sizeTileMapX-1; i > -1; i--) {
				free((*map)->tileMap[i]);
			}
			(*map)->tileMap = NULL;
		}
		free(*map);
		*map = NULL;
	}
}

int addMapTile(Map** map, int x, int y, int width, int height) {
	if (*map != NULL) {
		if ((*map)->srcRect == NULL) {
			(*map)->srcRect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
			if ((*map)->srcRect == NULL) {
				printf("Error! (*map)->rect could not initialize!\n");
				return -1;
			}
			(*map)->srcRect[(*map)->tiles].x = x;
			(*map)->srcRect[(*map)->tiles].y = y;
			(*map)->srcRect[(*map)->tiles].w = width;
			(*map)->srcRect[(*map)->tiles].h = height;
			(*map)->tiles++;
		} else {
			SDL_Rect* tmpRectRealloc = (SDL_Rect*)realloc((*map)->srcRect, sizeof(SDL_Rect) * ((*map)->tiles + 1));
			if (tmpRectRealloc == NULL) {
				printf("Error! tmpRectRealloc could not initialize!\n");
				return -1;
			}
			(*map)->srcRect = tmpRectRealloc;
			(*map)->srcRect[(*map)->tiles].x = x;
			(*map)->srcRect[(*map)->tiles].y = y;
			(*map)->srcRect[(*map)->tiles].w = width;
			(*map)->srcRect[(*map)->tiles].h = height;
			(*map)->tiles++;
		}
		return 1;
	}
	return -1;
}

void drawMapOnIndex(Window** window, Map** map, int index, int x, int y, int dstWidth, int dstHeight) {
	if (*map != NULL) {
		if ((index > -1) && (index < (*map)->tiles)) {
			(*map)->dstRect.x = x;
			(*map)->dstRect.y = y;
			(*map)->dstRect.w = dstWidth;
			(*map)->dstRect.h = dstHeight;
			SDL_RenderCopyEx((*window)->sdl_renderer, (*map)->sprite->sdl_texture, &((*map)->srcRect[index]), &((*map)->dstRect), (*map)->sprite->angle, NULL, (*map)->sprite->flip);
			if ((*map)->sprite->showRect) {
				SDL_SetRenderDrawColor((*window)->sdl_renderer, (*map)->sprite->colorRect.r, (*map)->sprite->colorRect.g, (*map)->sprite->colorRect.b, (*map)->sprite->colorRect.a);
				SDL_RenderDrawRect((*window)->sdl_renderer, &((*map)->dstRect));
			}
		}
	}
}

int drawMap(Window** window, Map** map, int x, int y, int dstWidth, int dstHeight) {
	if (*map != NULL) {
		int i, j, tile;
		for (i = 0; i < (*map)->sizeTileMapX; i++) {
			for (j = 0; j < (*map)->sizeTileMapY; j++) {
				tile = (*map)->tileMap[i][j];
				if (tile != (*map)->ignoredIndex) {
					(*map)->dstRect.x = (j * dstHeight) + x;
					(*map)->dstRect.y = (i * dstWidth) + y;
					(*map)->dstRect.w = dstWidth;
					(*map)->dstRect.h = dstWidth;
					SDL_RenderCopyEx((*window)->sdl_renderer, (*map)->sprite->sdl_texture, &((*map)->srcRect[tile]), &((*map)->dstRect), (*map)->sprite->angle, NULL, (*map)->sprite->flip);
					if ((*map)->sprite->showRect) {
						SDL_SetRenderDrawColor((*window)->sdl_renderer, (*map)->sprite->colorRect.r, (*map)->sprite->colorRect.g, (*map)->sprite->colorRect.b, (*map)->sprite->colorRect.a);
						SDL_RenderDrawRect((*window)->sdl_renderer, &((*map)->dstRect));
					}
				}
			}
		}
	}
}

// get functions
Sprite* getMapSprite(Map* map) {
	if (map != NULL) {
		return map->sprite;
	}

	return NULL;
}

SDL_Rect* getMapSrcRect(Map* map) {
	if (map != NULL) {
		return map->srcRect;
	}

	return NULL;
}

SDL_Rect getMapDstRect(Map* map) {
	if (map != NULL) {
		return map->dstRect;
	}

	return (SDL_Rect) { 0, 0, 0, 0 };
}

int** getTileMap(Map* map) {
	if (map != NULL) {
		return map->tileMap;
	}

	return NULL;
}

char* getMapPath(Map* map) {
	if (map != NULL) {
		return map->mapPath;
	}

	return NULL;
}

int getMapTiles(Map* map) {
	if (map != NULL) {
		return map->tiles;
	}

	return 0;
}

int getMapSizeTileMapX(Map* map) {
	if (map != NULL) {
		return map->sizeTileMapX;
	}

	return 0;
}

int getMapSizeTileMapY(Map* map) {
	if (map != NULL) {
		return map->sizeTileMapY;
	}

	return 0;
}

int getMapIgnoredIndex(Map* map) {
	if (map != NULL) {
		return map->ignoredIndex;
	}

	return 0;
}

// set procedures
void setMapSprite(Map** map, Sprite* sprite) {
	if (*map != NULL) {
		(*map)->sprite = sprite;
	}
}

void setMapSrcRect(Map** map, SDL_Rect* srcRect) {
	if (*map != NULL) {
		(*map)->srcRect = srcRect;
	}
}

void setMapDstRect(Map** map, SDL_Rect dstRect) {
	if (*map != NULL) {
		(*map)->dstRect = dstRect;
	}
}

void setTileMap(Map** map, int** tileMap) {
	if (*map != NULL) {
		(*map)->tileMap = tileMap;
	}
}

void setMapPath(Map** map, char* mapPath) {
	if (*map != NULL) {
		(*map)->mapPath = (char*)malloc(sizeof(char) * (strlen(mapPath) + 1));
		if ((*map)->mapPath == NULL) {
			printf("Error! newMap->mapPath could not initialize!\n");
			return NULL;
		}
		strcpy((*map)->mapPath, mapPath);
	}
}

void setMapTiles(Map** map, int tiles) {
	if (*map != NULL) {
		(*map)->tiles = tiles;
	}
}

void setMapSizeTileMapX(Map** map, int sizeTileMapX) {
	if (*map != NULL) {
		(*map)->sizeTileMapX = sizeTileMapX;
	}
}

void setMapSizeTileMapY(Map** map, int sizeTileMapY) {
	if (*map != NULL) {
		(*map)->sizeTileMapY = sizeTileMapY;
	}
}

void setMapIgnoredIndex(Map** map, int ignoredIndex) {
	if (*map != NULL) {
		(*map)->ignoredIndex = ignoredIndex;
	}
}