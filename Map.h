#pragma once
#include "MapEnumeration.h"
#include "Graphics.h"

class Map :
	public Renderable
{
private:
	int const* MAP_WIDTH;
	int const* MAP_HEIGHT;
	int const MAP_TILE_WIDTH_HEIGHT = 16;

	Uint8*** map;
	Graphics* graphics;

public:
	Map(Graphics* graphics, const int* MAP_WIDTH, const int* MAP_HEIGHT);
	~Map();

	int getTileAttribute(int x, int y, MapEnumeration::MAP_TILE_ATTRIBUTE attr);
	void generateMap(int sheerUp, int sheerDown, int initHeight);
	void render();
};

