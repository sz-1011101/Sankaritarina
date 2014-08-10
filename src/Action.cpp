#include "Action.h"
#include "Entity.h"

//Constructor, takes entity pointer to perform action on
Action::Action(Entity* entity)
{
	this->entity = entity;
	actionDone = false;
	actionStarted = false;
	amountProcessed = 0;
}

//Destructor
Action::~Action()
{
}

bool Action::isActionDone()
{
	return actionDone;
}

void Action::process(int framerate)
{

}