//This class controls all entity actions
#pragma once
#include <vector>
#include "Entity.h"
#include "Tree.h"
#include "Map.h"
#include "World.h"

class EntityControl
{
public:

	int const MAX_ENTITIES = 128;

	EntityControl(Map* map, Graphics* graphics, World* world);
	~EntityControl();
	bool removeEntity(Entity* entity);
	Tree* spawnTree(int x, int y);
	void entityInteraction(int framerate);
	
private:

	std::vector<Entity*> entities;
	std::vector<Entity*>::iterator entityIterator;
	Map* map;
	World* world;
	Graphics* graphics;
	const int TREE_FRAME_WIDTH = 64;
	const int TREE_FRAME_HEIGHT = 64;
	const int TREE_FRAMECOUNT = 7;

	
	bool addNewEntity(Entity* entity);

	void collisionsMap(Entity* entity);
};

