#pragma once
#include "MapEnumeration.h"
#include "Graphics.h"

class World;

class EntityControl;

class Map :
	public Renderable
{
public:

	int const* MAP_WIDTH;
	int const* MAP_HEIGHT;
	int const MAP_TILE_WIDTH_HEIGHT = 8;

	Map(Graphics* graphics, const int* MAP_WIDTH, const int* MAP_HEIGHT, World* world);
	~Map();

	int getTileAttribute(int x, int y, MapEnumeration::MAP_TILE_ATTRIBUTE attr);
	void generateMap(int sheerUp, int sheerDown, int initHeight, int treeRate, EntityControl* entityControl);
	int getHeightSegment(int x);
	virtual void render();

private:

	World* world;
	Uint8*** map;
	Uint8* segHeight;
	Graphics* graphics;
};

