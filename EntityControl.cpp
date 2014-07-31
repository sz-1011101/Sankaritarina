
#include <iterator>
#include <stdio.h>
#include <algorithm>

#include "EntityControl.h"
#include "TexturesEnumeration.h"


//Constructor
EntityControl::EntityControl(Map* map, Graphics* graphics, World* world)
{
	this->map = map;
	this->graphics = graphics;
	this->world = world;
}

//Deconstructor
EntityControl::~EntityControl()
{
	//Iterate over all entity elements and proceed
	for (entityIterator = entities.begin(); entityIterator != entities.end(); entityIterator++)
	{
		delete *entityIterator;
	}
	entities.clear();
}

//Add a new entity at the end of the entities vector
bool EntityControl::addNewEntity(Entity* entity)
{
	//Entity addable?
	if ((int)entities.size() < MAX_ENTITIES)
	{
		entities.push_back(entity);
		printf("Entity added, current size= %i\n", entities.size());
		return true;
	}
	else
	{
		return false;
	}
	
}

//Remove entity with index i
bool EntityControl::removeEntity(Entity* entity)
{
	
	std::vector<Entity*>::iterator posToRemove = std::find(entities.begin(), entities.end(), entity);
	//Check if found
	if (posToRemove != entities.end())
	{
		delete *posToRemove;
		entities.erase(posToRemove);
		printf("Entity removed, current size= %i\n", entities.size());
		return true;
	}
	
	
}

//Handles the interaction between entities
void EntityControl::entityInteraction(int framerate)
{
	//Iterate over all entity elements and proceed
	for (entityIterator = entities.begin(); entityIterator != entities.end(); entityIterator++)
	{
		(*entityIterator)->proceed(framerate);
		graphics->drawRenderable(*entityIterator); //Clear for rendering
	}
}

//Handles collisions of an entity with the map
void EntityControl::collisionsMap(Entity* entity)
{

}

//Spawns a tree, returns pointer if successful, NULL otherwise
Tree* EntityControl::spawnTree(int x, int y)
{
	Tree* spawnedTree = new Tree(x, y, graphics, graphics->getTextures(TexturesEnumeration::TEXTURE_TREE), &TREE_FRAMECOUNT, &TREE_FRAME_WIDTH, &TREE_FRAME_HEIGHT, world);
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