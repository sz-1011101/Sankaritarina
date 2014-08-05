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
#include "Text.h"


//Constructor
EntityControl::EntityControl(Map* map, Graphics* graphics, World* world)
{
	this->map = map;
	this->graphics = graphics;
	this->world = world;
	entities.reserve(MAX_ENTITIES); //Reserve enough space for the vector
	idCounter = 0;
	//Initialize entity zones

	amountZones = ceil(map->getMapWidth() / 30.0); //The map gets partitioned in zones of 30 tiles

	entityZones = new EntityZone[amountZones];

	//Give the numbers of the zone, for debugging reasons
	for (int i = 0; i < amountZones; i++)
	{
		entityZones[i].setZoneNumber(i);
	}
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
		entities.push_back(entity); //Add the Entity
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
	
	vegetationHandling(); //Spawn more trees
	entityZonesHandling(); //Assign zone

	//-----------------Entity Removal and rendering------------------------//
	std::vector<Entity*>::iterator entityIterator = entities.begin();
	//Run over alle entities
	while (entityIterator != entities.end())
	{
		if ((*entityIterator)->flaggedForRemoval())
		{
			//Remove this from the zone
			(*entityIterator)->getCurrentEntityZone()->removeEntityFromZone((*entityIterator)->getId());
			delete (*entityIterator); //Deallocate
			entityIterator = entities.erase(entityIterator); //erase and put at new position
			printf("Entity removed, current total= %i,current capacity= %i\n", entities.size(), entities.capacity());
		}
		else
		{
			(*entityIterator)->proceed(framerate);
			graphics->drawRenderable(*entityIterator,true); //Clear for rendering
			entityIterator++;
		}
	}
	//--------------------------Entity debug text--------------------------//
	entityDebugTextHandling();

}

//Handles collisions of an entity with the map
void EntityControl::collisionsMap(Entity* entity)
{
	/*
	TODO
	*/
}

//Spawns a tree, returns pointer if successful, NULL otherwise
Tree* EntityControl::spawnTree(int tileX, int tileY, bool seeded)
{
	int xPos = tileX*(map->MAP_TILE_WIDTH_HEIGHT) - 24;
	int yPos = ((map->getMapHeight() - 1) - tileY)*map->MAP_TILE_WIDTH_HEIGHT - 56;
	Tree* spawnedTree = new Tree(xPos, yPos, graphics, graphics->getTextures(TexturesEnumeration::TEXTURE_TREE), &TREE_FRAMECOUNT, &TREE_FRAME_WIDTH, &TREE_FRAME_HEIGHT, world, seeded, ++idCounter);
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
//TODO Change the zones so that they use hashmaps
void EntityControl::entityZonesHandling()
{

	int zone;

	//Run over all entities and put in zone
	for (std::vector<Entity*>::iterator entityIterator = entities.begin(); entityIterator != entities.end(); entityIterator++)
	{
		zone = ((*entityIterator)->getX() / map->MAP_TILE_WIDTH_HEIGHT) / ZONE_WIDTH;
		EntityZone* oldEntityZone = (*entityIterator)->getCurrentEntityZone();
		EntityZone* newEntityZone = &entityZones[zone];

		//Check if the zones have changed, and correct if needed
		if (oldEntityZone != NULL)
		{

			if (oldEntityZone != newEntityZone)
			{
				(*entityIterator)->setCurrentEntityZone(newEntityZone);
				newEntityZone->addEntityToZone(*entityIterator, (*entityIterator)->getId());
				oldEntityZone->removeEntityFromZone((*entityIterator)->getId());
			}
		}
		else //Otherwise set the zone for the first time
		{
			(*entityIterator)->setCurrentEntityZone(newEntityZone);
			newEntityZone->addEntityToZone(*entityIterator, (*entityIterator)->getId());
		}
		
	}
}

//Handles the debug text output for entities
void EntityControl::entityDebugTextHandling()
{
	//Run over all entities
	for (std::vector<Entity*>::iterator entityIterator = entities.begin(); entityIterator != entities.end(); entityIterator++)
	{
		graphics->drawRenderable((*entityIterator)->getDebugText(),true);
	}
}