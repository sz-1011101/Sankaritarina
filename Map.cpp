//This class handles map generation and handling
#include "Map.h"
#include "MapEnumeration.h"
#include "TexturesEnumeration.h"
#include "Functions.h"
#include "Graphics.h"
#include "EntityControl.h"
#include "World.h"


#include <stdio.h>

//Basic Map object constructor
Map::Map(Graphics* graphics, int mapWidth, int mapHeight, World* world)
{
	//set to 0, since the map streches over the entire level
	x = 0;
	y = 0;
	this->graphics = graphics;

	//init the constants
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
	map = new Uint8**[mapWidth];
	//Initialize the 3-dimensional matrix
	for (int i = 0; i < mapWidth; i++)
	{
		map[i] = new Uint8*[mapHeight];
		for (int j = 0; j < mapHeight; j++)
		{
			map[i][j] = new Uint8[MapEnumeration::MAP_TILE_ATR_TOTAL];
		}
	}
	//Initialize height array
	segHeight = new Uint8[mapWidth];

	this->world = world;
}

//Map destructor
Map::~Map()
{
	//free all allocated memory
	for (int i = 0; i < mapWidth; i++)
	{
		for (int j = 0; j < mapHeight; j++)
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
	if (x >= mapWidth || y >= mapHeight || x < 0 || y < 0)
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
void Map::generateMap(int sheerUp, int sheerDown, int initHeight, int treeRate, EntityControl* entityControl)
{
	printf("Generating map...\n");
	const int FLATTING = 4; //how long the earth will be flatted
	int groundHeight = initHeight;
	bool entityPut = false;
	int flattedTiles = FLATTING;

	for (int i = 0; i < mapWidth; i++)
	{
		//Determine the grounds height or in case of placed entity, do nothing
		if (!entityPut)
		{
			groundHeight = groundHeight + Functions::generateRandomNumber(-sheerDown, sheerUp);
		}
		else if (flattedTiles>0)
		{
			flattedTiles--;
		}
		else
		{
			flattedTiles = FLATTING;
			entityPut = false;
		}

		//catch numbers which are too low (negative and 0)
		if (groundHeight <= 1) {
			groundHeight = 1;
		}
		//Set the segment's height
		segHeight[i] = groundHeight;
		//From the ground up create earth
		for (int j = mapHeight - 1; j >= 0; j--)
		{
			//Place earth until upper limit reached (note that the y axis is "inverse")
			if (j > (mapHeight - 1) - groundHeight)
			{
				map[i][j][MapEnumeration::MAP_TILE_ATR_TYPE] = MapEnumeration::MAP_TILE_TYPE_EARTH;
			}
			else
			{
				map[i][j][MapEnumeration::MAP_TILE_ATR_TYPE] = MapEnumeration::MAP_TILE_TYPE_EMTPY;
			}
		}
		//Plant a tree with a random chance
		if (!entityPut && Functions::generateRandomNumber(0, 100) < treeRate)
		{
			//spawn with a little offset to the left and up, also the earth should be flat around a tree
			entityControl->spawnTree(i, groundHeight, false);
			entityPut = true;
		}

	}
}


int Map::getHeightSegment(int x)
{
	return segHeight[x];
}

//Render the map via graphics
void Map::render()
{
	//Draw Background
	graphics->drawBackground(world->getRedSkyColor(), world->getGreenSkyColor(), world->getBlueSkyColor());

	int cameraX = graphics->getCameraX();
	int cameraY = graphics->getCameraY();

	//Only render a part of the map matrix, since the rest will be invisible anyway
	int firstIndexX = graphics->getCameraX() / MAP_TILE_WIDTH_HEIGHT;
	int lastIndexX = firstIndexX + (*graphics->SCREEN_WIDTH / MAP_TILE_WIDTH_HEIGHT) + 1;

	int firstIndexY = graphics->getCameraY() / MAP_TILE_WIDTH_HEIGHT;
	int lastIndexY = firstIndexY + (*graphics->SCREEN_HEIGHT / MAP_TILE_WIDTH_HEIGHT) + 1;

	//Check if firstIndex, lastIndex aren't violating array length
	if (firstIndexX < 0)
	{
		firstIndexX = 0;
	}
	if (lastIndexX >= mapWidth)
	{
		lastIndexX = mapWidth - 1;
	}

	if (firstIndexY < 0)
	{
		firstIndexY = 0;
	}
	if (lastIndexY >= mapHeight)
	{
		lastIndexY = mapHeight - 1;
	}

	TexturesEnumeration::TEXTURES_NAME textureToDraw = TexturesEnumeration::TEXTURE_EMPTY;

	//render everything
	for (int i = firstIndexX; i < lastIndexX; i++)
	{
		for (int j = firstIndexY; j < lastIndexY; j++)
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
			//color mod by worlds lighting for the surface tile
			if (mapHeight - j == segHeight[i])
			{

				graphics->setTextureColorMod(textureToDraw, world->getRedColorMod(), world->getGreenColorMod(), world->getBlueColorMod());
			}
			else
			{
				graphics->setTextureColorMod(textureToDraw, 255, 255, 255);
			}
			graphics->drawTexture(textureToDraw, i * MAP_TILE_WIDTH_HEIGHT, j * MAP_TILE_WIDTH_HEIGHT, MAP_TILE_WIDTH_HEIGHT, MAP_TILE_WIDTH_HEIGHT, true);

		}
	}
}

int Map::getMapWidth()
{
	return mapWidth;
}

int Map::getMapHeight()
{
	return mapHeight;
}