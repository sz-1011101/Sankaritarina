//Wrapper class for the controller and entity
#include "EntityControllerPair.h"

#define NULL 0
//Constructor for a entity-controller pair
EntityControllerPair::EntityControllerPair(Entity* entity, Controller* controller)
{
	this->entity = entity;
	this->controller = controller;
}

//Destructor
EntityControllerPair::~EntityControllerPair()
{
	if (entity != NULL)
	{
		delete entity;
	}

	if (controller != NULL)
	{
		delete controller;
	}
}

//Entity Getter
Entity* EntityControllerPair::getEntity()
{
	return entity;
}

//Controller Getter
Controller* EntityControllerPair::getController()
{
	return controller;
}
