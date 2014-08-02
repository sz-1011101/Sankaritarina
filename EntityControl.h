#pragma once
#include <vector>
#include "Entity.h"
#include "Tree.h"
#include "Map.h"
#include "World.h"


class EntityControl
{
public:

	int const MAX_ENTITIES = 512;
	int const MAX_TREES = MAX_ENTITIES / 4;

	EntityControl(Map* map, Graphics* graphics, World* world);
	~EntityControl();
	Tree* spawnTree(int tileX, int tileY, bool seeded);
	void populateMap(Map* map);
	void entityInteraction(int framerate);

private:

	std::vector<Entity*> entities;
	Map* map;
	World* world;
	Graphics* graphics;
	const int TREE_FRAME_WIDTH = 64;
	const int TREE_FRAME_HEIGHT = 64;
	const int TREE_FRAMECOUNT = 8;


	bool addNewEntity(Entity* entity);
	void collisionsMap(Entity* entity);
	void vegetationHandling();
};

