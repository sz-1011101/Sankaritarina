//This class handles map generation and handling
#include "Map.h"
#include "MapEnumeration.h"
#include "TexturesEnumeration.h"
#include "Functions.h"
#include "Graphics.h"
#include <stdio.h>

//Basic Map object constructor
Map::Map(Graphics* graphics, const int* MAP_WIDTH, const int* MAP_HEIGHT)
{
	//set to 0, since the map streches over the entire level
	x = 0;
	y = 0;
	this->graphics = graphics;
	//init the constants
	this->MAP_WIDTH = MAP_WIDTH;
	this->MAP_HEIGHT = MAP_HEIGHT;
	map = new Uint8**[*MAP_WIDTH];
	//Initialize the 3-dimensional matrix
	for (int i = 0; i < *MAP_WIDTH; i++)
	{
		map[i] = new Uint8*[*MAP_HEIGHT];
		for (int j = 0; j < *MAP_HEIGHT; j++)
		{
			map[i][j] = new Uint8[MapEnumeration::MAP_TILE_ATR_TOTAL];
		}
	}
}

//Map destructor
Map::~Map()
{
	//free all allocated memory
	for (int i = 0; i < *MAP_WIDTH; i++)
	{
		for (int j = 0; j < *MAP_HEIGHT; j++)
		{
			delete[] map[i][j];
		}
		delete[] map[i];
	}
	delete[] map;
}

//Retrieves the value of an map tile attribute, returns -1 if invalid value
int Map::getTileAttribute(int x, int y, MapEnumeration::MAP_TILE_ATTRIBUTE attr)
{
	//check if valid position
	if (x >= *MAP_WIDTH || y >= *MAP_HEIGHT || x < 0 || y < 0)
	{
		return -1;
	}

	return map[x][y][attr];
}

/*Generates a basic randomized Map
	sheerUp how many tiles the height can differ from the previous height (upper limit)
	sheerDown how many tiles the height can differ from the previous height (lower limit)
	initHeight the height of the first segment
*/
void Map::generateMap(int sheerUp, int sheerDown, int initHeight)
{
	printf("Generating map...\n");
	
	int groundHeight = initHeight;

	for (int i = 0; i < *MAP_WIDTH; i++)
	{
		groundHeight = groundHeight+Functions::generateRandomNumber(-sheerDown, sheerUp);
		//catch numbers which are too low (negative)
		if (groundHeight <= 1) {
			groundHeight = 1;
		}
		//From the ground up create earth
		for (int j = *MAP_HEIGHT-1; j >= 0; j--)
		{
			//Place earth until upper limit reached
			if (j >(*MAP_HEIGHT-1) - groundHeight)
			{
				map[i][j][MapEnumeration::MAP_TILE_ATR_TYPE] = MapEnumeration::MAP_TILE_TYPE_EARTH;
			}
			else
			{
				map[i][j][MapEnumeration::MAP_TILE_ATR_TYPE] = MapEnumeration::MAP_TILE_TYPE_EMTPY;
			}
		}
	}
}

//Render the map via graphics
void Map::render()
{

	int cameraX = graphics->getCameraX();
	int cameraY = graphics->getCameraY();

	//Only render a part of the map matrix, since the rest will be invisible anyway
	int firstIndexX = graphics->getCameraX() / MAP_TILE_WIDTH_HEIGHT;
	int lastIndexX = firstIndexX + (*graphics->SCREEN_WIDTH / MAP_TILE_WIDTH_HEIGHT)+1;

	//Check if firstIndex, lastIndex aren't violating array length
	if (firstIndexX < 0)
	{
		firstIndexX = 0;
	}
	if (lastIndexX >= *MAP_WIDTH)
	{
		lastIndexX = *MAP_WIDTH - 1;
	}

	TexturesEnumeration::TEXTURES_NAME textureToDraw = TexturesEnumeration::TEXTURE_EMPTY;

	//render everything
	for (int i = firstIndexX; i < lastIndexX; i++)
	{
		for (int j = 0; j < *MAP_HEIGHT; j++)
		{
			switch (map[i][j][0])
			{
			case MapEnumeration::MAP_TILE_TYPE_EMTPY: 
				textureToDraw = TexturesEnumeration::TEXTURE_EMPTY;
				break;
			case MapEnumeration::MAP_TILE_TYPE_EARTH:
				textureToDraw = TexturesEnumeration::TEXTURE_EARTH;
				break;
			}
			graphics->drawTexture(textureToDraw, i * 16, j * 16, 16, 16, true);
			
		}
	}
}