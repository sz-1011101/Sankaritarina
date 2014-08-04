//This class controls all entity actions

#include <iterator>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>

#include "EntityControl.h"
#include "TexturesEnumeration.h"
#include "Functions.h"
#include "EntityControl.h"
#include "EntityZone.h"


//Constructor
EntityControl::EntityControl(Map* map, Graphics* graphics, World* world)
{
	this->map = map;
	this->graphics = graphics;
	this->world = world;
	entities.reserve(MAX_ENTITIES); //Reserve enough space for the vector

	//Initialize entity zones

	amountZones = ceil(map->getMapWidth() / 30.0); //The map gets partitioned in zones of 30 tiles
	entityZones = new EntityZone[amountZones];
}

//Deconstructor
EntityControl::~EntityControl()
{
	std::vector<Entity*>::iterator entityIterator;
	//Iterate over all entity elements and proceed
	for (entityIterator = entities.begin(); entityIterator != entities.end(); entityIterator++)
	{
		delete *entityIterator;
	}
	entities.clear();
	//Deallocate the zones
	delete[] entityZones;

}

//Add a new entity at the end of the entities vector
bool EntityControl::addNewEntity(Entity* entity)
{
	//Entity addable?
	if ((int)entities.size() < MAX_ENTITIES)
	{
		entities.push_back(entity);
		printf("Entity added, current total= %i,current capacity= %i\n", entities.size(), entities.capacity());
		return true;
	}
	else
	{
		return false;
	}

}

//Handles the interaction between entities
//TODO check this for memleaks and safty
void EntityControl::entityInteraction(int framerate)
{
	//-----------------------Entity Handling-------------------------------//
	entityZonesHandling(); //Assign zone
	vegetationHandling(); //Spawn more trees

	//-----------------Entity Removal and rendering------------------------//
	std::vector<Entity*>::iterator entityIterator = entities.begin();
	//Run over alle entities
	while (entityIterator != entities.end())
	{
		if ((*entityIterator)->flaggedForRemoval())
		{
			delete (*entityIterator); //Deallocate
			entityIterator = entities.erase(entityIterator); //erase and put at new position
			printf("Entity removed, current total= %i,current capacity= %i\n", entities.size(), entities.capacity());
		}
		else
		{
			(*entityIterator)->proceed(framerate);
			graphics->drawRenderable(*entityIterator); //Clear for rendering
			entityIterator++;
		}
	}

}

//Handles collisions of an entity with the map
void EntityControl::collisionsMap(Entity* entity)
{

}

//Spawns a tree, returns pointer if successful, NULL otherwise
Tree* EntityControl::spawnTree(int tileX, int tileY, bool seeded)
{
	int xPos = tileX*(map->MAP_TILE_WIDTH_HEIGHT) - 24;
	int yPos = ((map->getMapHeight() - 1) - tileY)*map->MAP_TILE_WIDTH_HEIGHT - 56;
	Tree* spawnedTree = new Tree(xPos, yPos, graphics, graphics->getTextures(TexturesEnumeration::TEXTURE_TREE), &TREE_FRAMECOUNT, &TREE_FRAME_WIDTH, &TREE_FRAME_HEIGHT, world, seeded);
	//return if successful
	if (addNewEntity(spawnedTree))
	{
		return spawnedTree;
	}
	else
	{
		delete spawnedTree; //deallocate the now useless object
		return NULL;
	}

}

//Handles vegetation growth and death on the map
void EntityControl::vegetationHandling()
{
	if (entities.size() < MAX_TREES)
	{
		int randomTreePosX = Functions::generateRandomNumber(0, map->getMapWidth() - 1);
		spawnTree(randomTreePosX, map->getHeightSegment(randomTreePosX), true);
	}
}

//Puts the Entities in their respective zones
void EntityControl::entityZonesHandling()
{
	//Clear all zones
	for (int i = 0; i < amountZones; i++)
	{
		entityZones[i].entities.clear();
	}

	int zone;

	//Run over all entities and put in zone
	for (std::vector<Entity*>::iterator entityIterator = entities.begin(); entityIterator != entities.end(); entityIterator++)
	{
		zone = ((*entityIterator)->getX() / map->MAP_TILE_WIDTH_HEIGHT) / ZONE_WIDTH;
		(*entityIterator)->setCurrentEntityZone(&entityZones[zone]);
		entityZones[zone].entities.push_back((*entityIterator));
	}
}