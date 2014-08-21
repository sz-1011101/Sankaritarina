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
		if (decisionCooldown >= DECICION_COOLDOWN_THRESHOLD_STANDARD)
		{
			decisionCooldown = 0;
			Animal* animal = (Animal*)entity;

			//Check if action pointer is clear
			if (animal->getAction() == NULL)
			{

				//Give a random movement action with 33% probability
				if (Functions::calculateRandomBoolean(33))
				{

					//Move left or right with 50% probability
					if (Functions::calculateRandomBoolean(50))
					{
						action = new MovementAction(entity, ((Animal*)entity)->MAX_MOVEMENT_ONE_STEP, 0);
						animal->setActionStatus(AnimalEnumeration::ANIMAL_ACTION_MOVING);
					}
					else
					{
						action = new MovementAction(entity, (-1)*((Animal*)entity)->MAX_MOVEMENT_ONE_STEP, 0);
						animal->setActionStatus(AnimalEnumeration::ANIMAL_ACTION_MOVING);
					}

					animal->setAction(action);
				}
				else
				{
					animal->setActionStatus(AnimalEnumeration::ANIMAL_ACTION_IDLE); //Otherwise set idle
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