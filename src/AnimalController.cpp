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

	using namespace AnimalEnumeration;

	Action* action = NULL;

	switch (((Animal*)entity)->getAnimalState())
	{
	case ANIMAL_UNBORN: //Do nothing if animal not born yet
		break;
	default:
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
		break;
	}

	return ((Action*)action);
}