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
	int getMapWidth();
	int getMapHeight();
	int getTileXFromPosition(int x);
	int getHeightSegment(int x);
	int getGraphicalHeightSegment(int x);
	int getGraphicalHeightSegmentTile(int x);

	virtual void render();

private:

	int mapWidth;
	int mapHeight;
	World* world;
	Uint8*** map;
	Uint8* segHeight;
	Graphics* graphics;

	bool checkTileVisible(int tileX, int tileY);

};

