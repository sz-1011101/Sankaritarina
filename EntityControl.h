#pragma once
#include <vector>

#include "Entity.h"
#include "Map.h"
#include "World.h"


class EntityZone;
class Tree;
class Animal;

class EntityControl
{
public:

	const int  MAX_ENTITIES = 128;
	const int MAX_TREES = MAX_ENTITIES / 8;
	const int MAX_ANIMALS = MAX_ENTITIES / 4;
	const int ZONE_WIDTH = 30;
	const bool ENTITY_DEBUGGING_ACTIVE = true;

	EntityControl(Map* map, Graphics* graphics, World* world);
	~EntityControl();

	Tree* spawnTree(int tileX, int tileY, bool seeded);
	Animal* spawnAnimal(int tileX, int tileY, bool born);

	void populateMap(Map* map);
	void entityInteraction(int framerate);

private:

	const int TREE_FRAME_WIDTH = 64;
	const int TREE_FRAME_HEIGHT = 64;
	const int TREE_FRAMECOUNT = 8;
	const int TREE_WEIGHT = 1000;
	const int TREE_FRAME_CENTER_OFFSET = 20;

	const int CHICKEN_FRAME_WIDTH = 16;
	const int CHICKEN_FRAME_HEIGHT = 8;
	const int CHICKEN_FRAMECOUNT = 10;
	const int CHICKEN_WEIGHT = 1;
	const int CHICKEN_FRAME_CENTER_OFFSET = 5;

	std::vector<Entity*> entities;
	EntityZone* entityZones;
	Map* map;
	World* world;
	Graphics* graphics;
	int amountZones;
	int idCounter;

	bool addNewEntity(Entity* entity);
	void vegetationHandling();
	void animalsHandling();
	void updateZone(Entity* entity);
	void renderDebugText(Entity* entity);

};

