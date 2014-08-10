#define NULL 0
#include "AnimalController.h"
#include "Animal.h"
#include "Functions.h"
#include "MovementAction.h"

//Constructor
AnimalController::AnimalController(Animal* entity, Map* map) : Controller(entity, map)
{

}

//Destructor
AnimalController::~AnimalController()
{

}

//Decide an action
Action* AnimalController::decideAction(int framerate)
{
	Action* action = NULL;

	//Check if its already time for a new decicion
	if (decisionCooldown >= DECICION_COOLDOWN_THRESHOLD)
	{
		decisionCooldown = 0;
		if (((Animal*)entity)->getAction() == NULL)
		{
			if (Functions::calculateRandomBoolean(33))
			{
				if (Functions::calculateRandomBoolean(50))
				{
					action = new MovementAction(entity, ((Animal*)entity)->MAX_MOVEMENT_ONE_STEP, 0);

				}
				else
				{
					action = new MovementAction(entity, (-1)*((Animal*)entity)->MAX_MOVEMENT_ONE_STEP, 0);
				}

				((Animal*)entity)->setAction(action);
			}
		}
	}
	else
	{
		decisionCooldown = decisionCooldown + 1 * Functions::calculateFrameFactor(framerate);
	}


	return ((Action*)action);
}