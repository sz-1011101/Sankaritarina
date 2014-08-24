//A MovementAction pushes an object into a direction and sets it's heading
#include "MovementAction.h"
#include "Entity.h"
#include "Functions.h"

MovementAction::MovementAction(Entity* entity, double x, double y) : Action(entity)
{
	this->x = x;
	this->y = y;
}


MovementAction::~MovementAction()
{

}

//Give the entity a push in the given direction
void MovementAction::process(int framerate)
{
	using namespace EntityEnumeration;

	if (!actionStarted)
	{
		//push the object
		entity->push(x, y, framerate, true);
		//set it's heading
		if (x > 0)
		{
			entity->setHeading(RIGHT);
		}
		else if (x < 0)
		{
			entity->setHeading(LEFT);
		}

		actionStarted = true;
	}

	//This holds the action for some "time" active
	if (amountProcessed >= PROCESS_FOR_ITERATIONS)
	{
		actionDone = true;
	}

	//This action needs "time" to process some more
	amountProcessed = amountProcessed + 1 * Functions::calculateFrameFactor(framerate);

}