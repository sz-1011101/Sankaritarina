#include "Controller.h"
#include "Entity.h"
#include "Map.h"
#include "Action.h"

Controller::Controller(Entity* entity, Map* map)
{
	this->entity = entity;
	this->map = map;
	decisionCooldown = 0;
}


Controller::~Controller()
{
}

//decides an action for the corresponding entity and returns pointer to said action
Action* Controller::decideAction(int framerate)
{
	return NULL;
}
