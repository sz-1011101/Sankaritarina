#include "EntityZone.h"

//Constructor
EntityZone::EntityZone()
{
	this->zoneNumber = -1;
	entities.reserve(128);
}

//Destrcutor
EntityZone::~EntityZone()
{
	clearEntities();
}

//Add an entity to this zone
void EntityZone::addEntityToZone(Entity* entity, int id)
{
	entities[id] = entity;
}

void EntityZone::removeEntityFromZone(int id)
{
	entities.erase(id);
}

//clear all entities from the zone
void EntityZone::clearEntities()
{
	entities.clear();
}

//get the vector that contains all entities
std::unordered_map<int, Entity*>* EntityZone::getEntities()
{
	return &entities;
}

//Returns the currently set zone number
int EntityZone::getZoneNumber()
{
	return zoneNumber;
}

/*Set the current Zone number, if not set yet. Returns true if successfull, false otherwise.
Useful for debugging
*/
bool EntityZone::setZoneNumber(int zoneNumber)
{
	if (this->zoneNumber == -1)
	{
		this->zoneNumber = zoneNumber;
		return true;
	}
	else
	{
		return false;
	}
}
