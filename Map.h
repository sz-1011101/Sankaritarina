#pragma once
#include "MapEnumeration.h"
#include "Graphics.h"
#include "Renderable.h"

class World;
class EntityControl;

class Map :
	public Renderable
{
public:

	int const MAP_TILE_WIDTH_HEIGHT = 8;

	Map(Graphics* graphics, int MapWidth, int MapHeight, World* world);
	~Map();

	int getTileAttribute(int x, int y, MapEnumeration::MAP_TILE_ATTRIBUTE attr);
	void generateMap(int sheerUp, int sheerDown, int initHeight, int treeRate, EntityControl* entityControl);
	int getHeightSegment(int x);
	int getMapWidth();
	int getMapHeight();
	virtual void render();

private:

	int mapWidth;
	int mapHeight;
	World* world;
	Uint8*** map;
	Uint8* segHeight;
	Graphics* graphics;



};

