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

#include "Appletree.h"
#include "Chicken.h"
#include "Fox.h"

#include "AnimalController.h"
#include "EntityControllerPair.h"

//Constructor
EntityControl::EntityControl(Map* map, Graphics* graphics, World* world)
{
	this->map = map;
	this->graphics = graphics;
	this->world = world;
	entities.reserve(MAX_ENTITIES); //Reserve enough space for the vector
	idCounter = 0;

	//Initialize entity zones
	amountZones = (int)ceil(((double)map->getMapWidth()) / 30.0); //The map gets partitioned in zones of 30 tiles

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
	std::vector<EntityControllerPair*>::iterator entityIterator;

	//Iterate over all entity elements and proceed
	for (entityIterator = entities.begin(); entityIterator != entities.end(); entityIterator++)
	{
		delete *entityIterator;
	}
	entities.clear();
	//Deallocate the zones
	delete[] entityZones;

}

//Returns true if entities can be fitted into the vector
bool EntityControl::entitiesAddable()
{
	if ((int)entities.size() < MAX_ENTITIES)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//Add a new entity at the end of the entities vector, returns if successful
void EntityControl::addNewEntity(Entity* entity, Controller* controller)
{
	//Entity addable?
	if (entitiesAddable())
	{
		EntityControllerPair* entityControllerPair = new EntityControllerPair(entity, controller);
		entities.push_back(entityControllerPair);
		printf("Entity added, current total= %i,current capacity= %i\n", entities.size(), entities.capacity());
	}

}

//Handles the interaction between entities
void EntityControl::entityInteraction(int framerate)
{
	EntityControllerPair* currentEntity;
	//-----------------------Entity Handling-------------------------------//

	animalsHandling(); //Spawn more chicken
	vegetationHandling(); //Spawn more trees

	//-----------------Entity Removal and rendering------------------------//
	std::vector<EntityControllerPair*>::iterator entityIterator = entities.begin();
	//Run over all entities
	while (entityIterator != entities.end())
	{
		currentEntity = *entityIterator;
		if (currentEntity->getEntity()->flaggedForRemoval())
		{
			//Remove this from the zone, if it was assigned before
			if (currentEntity->getEntity()->getCurrentEntityZone() != NULL)
			{
				currentEntity->getEntity()->getCurrentEntityZone()->removeEntityFromZone(currentEntity->getEntity()->getId());
			}
			delete *entityIterator; //Deallocate
			entityIterator = entities.erase(entityIterator); //erase and put at new position
			printf("Entity removed, current total= %i,current capacity= %i\n", entities.size(), entities.capacity());
		}
		entityIterator++;
	}

	//Run over all entities again, and decide an action
	for (entityIterator = entities.begin(); entityIterator != entities.end(); entityIterator++)
	{
		currentEntity = *entityIterator;
		//Controller decides an action, if controller avaible
		if (currentEntity->getController() != NULL)
		{
			currentEntity->getController()->decideAction(framerate);
		}
	}


	//Run over all entities again and run everything
	for (entityIterator = entities.begin(); entityIterator != entities.end(); entityIterator++)
	{
		currentEntity = *entityIterator;
		//----------------Entity does stuff--------------------------------//

		currentEntity->getEntity()->updateForces(framerate);
		currentEntity->getEntity()->handleCollisions(framerate, map);
		currentEntity->getEntity()->proceed(framerate);

		updateZone(currentEntity->getEntity());


		graphics->drawRenderable(currentEntity->getEntity(), true); //Clear for rendering
		renderDebugText(currentEntity->getEntity()); //debug output
	}
}

//Spawns a tree, returns pointer if successful, NULL otherwise
Tree* EntityControl::spawnTree(int tileX, int tileY, bool seeded)
{
	int xPos = tileX*map->MAP_TILE_WIDTH_HEIGHT;
	int yPos = tileY*map->MAP_TILE_WIDTH_HEIGHT;

	//return if successful
	if (entitiesAddable())
	{
		Tree* spawnedTree = new Appletree(xPos, yPos, graphics, graphics->getTextures(TexturesEnumeration::TEXTURE_TREE), world, seeded, ++idCounter);

		addNewEntity(spawnedTree, NULL);

		return spawnedTree;
	}
	else
	{
		return NULL;
	}
}

//Spawns a chicken, returns pointer if successful, NULL otherwise
//born determines if the animal should be spawned as a "newborn (egg)" or not
Animal* EntityControl::spawnAnimal(int tileX, int tileY, bool born, AnimalEnumeration::ANIMALS animal)
{
	using namespace AnimalEnumeration;

	int xPos = tileX*map->MAP_TILE_WIDTH_HEIGHT;
	int yPos = tileY*map->MAP_TILE_WIDTH_HEIGHT;

	Animal* spawnedAnimal = NULL;

	//return if successful
	if (entitiesAddable())
	{
		//Decide animal based on provided value
		switch (animal)
		{
		case CHICKEN:
			spawnedAnimal = new Chicken(xPos, yPos, graphics, graphics->getTextures(TexturesEnumeration::TEXTURE_CHICKEN), world, map, born, ++idCounter);
			break;
		case FOX:
			spawnedAnimal = new Fox(xPos, yPos, graphics, graphics->getTextures(TexturesEnumeration::TEXTURE_FOX), world, map, born, ++idCounter);
			break;
		default:
			printf("Error: Couldn't spawn Animal\n");
			break;
		}

		//Create controller for this animal, which will decide actions for it
		Controller* controller = new AnimalController(spawnedAnimal, map); //The controller object for this entity, handles all ai interaction

		//check if valid pointers provided
		if (spawnedAnimal != NULL || controller != NULL)
		{
			addNewEntity(spawnedAnimal, controller);
		}
		else
		{
			printf("Error: Animal or Controller is NULL\n");
		}


		return spawnedAnimal;
	}
	else
	{
		return NULL;
	}
}

//Handles vegetation growth/spawning
void EntityControl::vegetationHandling()
{
	if ((int)entities.size() < MAX_ENTITIES)
	{
		int randomTreePosX = Functions::generateRandomNumber(0, map->getMapWidth() - 1);
		spawnTree(randomTreePosX, map->getGraphicalHeightSegmentTile(randomTreePosX), true);
	}
}

//Handles animal spawning
void EntityControl::animalsHandling()
{
	if ((int)entities.size() < MAX_ENTITIES)
	{
		int randomAnimalPosX = Functions::generateRandomNumber(0, map->getMapWidth() - 1);

		//Spawn a chicken for 50%, otherwise a fox
		if (Functions::calculateRandomBoolean(50))
		{
			spawnAnimal(randomAnimalPosX, map->getGraphicalHeightSegmentTile(randomAnimalPosX), true, AnimalEnumeration::FOX);
		}
		else
		{
			spawnAnimal(randomAnimalPosX, map->getGraphicalHeightSegmentTile(randomAnimalPosX), true, AnimalEnumeration::CHICKEN);
		}
		
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