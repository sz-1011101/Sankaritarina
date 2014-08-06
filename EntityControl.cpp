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
#include "Tree.h"
#include "Animal.h"

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

//Add a new entity at the end of the entities vector, returns if successful
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
	Entity* currentEntity;
	//-----------------------Entity Handling-------------------------------//

	animalsHandling(); //Spawn more chicken
	vegetationHandling(); //Spawn more trees

	//-----------------Entity Removal and rendering------------------------//
	std::vector<Entity*>::iterator entityIterator = entities.begin();
	//Run over alle entities
	while (entityIterator != entities.end())
	{
		currentEntity = *entityIterator;
		if (currentEntity->flaggedForRemoval())
		{
			//Remove this from the zone, if it was assigned before
			if (currentEntity->getCurrentEntityZone() != NULL)
			{
				currentEntity->getCurrentEntityZone()->removeEntityFromZone(currentEntity->getId());
			}
			delete (*entityIterator); //Deallocate
			entityIterator = entities.erase(entityIterator); //erase and put at new position
			printf("Entity removed, current total= %i,current capacity= %i\n", entities.size(), entities.capacity());
		}
		else
		{
			//----------------Entity does stuff--------------------------------//
			currentEntity->proceed(framerate);

			updateZone(currentEntity);


			graphics->drawRenderable(currentEntity, true); //Clear for rendering
			renderDebugText(currentEntity); //debug output


			entityIterator++;
		}
	}
}

//Spawns a tree, returns pointer if successful, NULL otherwise
//TODO optimize and make more simple
Tree* EntityControl::spawnTree(int tileX, int tileY, bool seeded)
{
	int xPos = tileX*(map->MAP_TILE_WIDTH_HEIGHT) - 24;
	int yPos = ((map->getMapHeight() - 1) - tileY)*map->MAP_TILE_WIDTH_HEIGHT - 56;
	Tree* spawnedTree = new Tree(xPos, yPos, TREE_WEIGHT, graphics, graphics->getTextures(TexturesEnumeration::TEXTURE_TREE), &TREE_FRAMECOUNT, &TREE_FRAME_WIDTH, &TREE_FRAME_HEIGHT, world, seeded, ++idCounter);
	
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

//Spawns a animal, returns pointer if successful, NULL otherwise
Animal* EntityControl::spawnAnimal(int tileX, int tileY, bool born)
{
	int xPos = tileX*(map->MAP_TILE_WIDTH_HEIGHT) - 24;
	int yPos = ((map->getMapHeight() - 1) - tileY)*map->MAP_TILE_WIDTH_HEIGHT - 56;
	Animal* spawnedAnimal = new Animal(xPos, yPos, CHICKEN_WEIGHT, graphics, graphics->getTextures(TexturesEnumeration::TEXTURE_CHICKEN), &CHICKEN_FRAMECOUNT, &CHICKEN_FRAME_WIDTH, &CHICKEN_FRAME_HEIGHT, world, born, ++idCounter);
	
	//return if successful
	if (addNewEntity(spawnedAnimal))
	{
		return spawnedAnimal;
	}
	else
	{
		delete spawnedAnimal; //deallocate the now useless object
		return NULL;
	}
}


//Handles vegetation growth/spawning
void EntityControl::vegetationHandling()
{
	if (entities.size() < MAX_ENTITIES)
	{
		int randomTreePosX = Functions::generateRandomNumber(0, map->getMapWidth() - 1);
		spawnTree(randomTreePosX, map->getHeightSegment(randomTreePosX), true);
	}
}

//Handles animal spawning
void EntityControl::animalsHandling()
{
	if (entities.size() < MAX_ENTITIES)
	{
		int randomAnimalPosX = Functions::generateRandomNumber(0, map->getMapWidth() - 1);
		spawnAnimal(randomAnimalPosX, map->getHeightSegment(randomAnimalPosX), true);
	}
}

//Puts the Entity in their respective zones, removes from old zone
//TODO Change the zones so that they use hashmaps
void EntityControl::updateZone(Entity* entity)
{
	//Run over all entities and put in zone
	int zone = (entity->getX() / map->MAP_TILE_WIDTH_HEIGHT) / ZONE_WIDTH;
	EntityZone* oldEntityZone = entity->getCurrentEntityZone();
	EntityZone* newEntityZone = &entityZones[zone];
	
	//Check if the zones have changed, and correct if needed
	if (oldEntityZone != NULL)
	{
		//Change detected?
		if (oldEntityZone != newEntityZone)
		{
			entity->setCurrentEntityZone(newEntityZone);
			newEntityZone->addEntityToZone(entity, entity->getId());
			oldEntityZone->removeEntityFromZone(entity->getId());
			printf("Reset zone for an entity\n");
		}
		
	}
	else //Otherwise set the zone for the first time
	{
		entity->setCurrentEntityZone(newEntityZone);
		newEntityZone->addEntityToZone(entity, entity->getId());
	}
}

//Renders the debug text of an entity
void EntityControl::renderDebugText(Entity* entity)
{
	//Run over all entities
	graphics->drawRenderable(entity->getDebugText(), true);


}