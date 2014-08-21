#pragma once
#include <vector>

#include "Entity.h"
#include "Map.h"
#include "World.h"


class EntityZone;
class Tree;
class Animal;
class Controller;
class EntityControllerPair;
class ControllerThreadPool;

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

	std::vector<EntityControllerPair*> entities;

	EntityZone* entityZones;
	Map* map;
	World* world;
	Graphics* graphics;
	ControllerThreadPool* controllerThreadPool;
	int amountZones;
	int idCounter;

	bool entitiesAddable();
	void addNewEntity(Entity* entity, Controller* controller);
	void vegetationHandling();
	void animalsHandling();
	void updateZone(Entity* entity);
	void renderDebugText(Entity* entity);

};

