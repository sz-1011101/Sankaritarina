//This class implements the chicken
#include "Chicken.h"
#include "Text.h"
#include "EntityZone.h"
#include "Action.h"
#include "AnimalController.h"

//Constructor for a chicken object
Chicken::Chicken(int x, int y, Graphics* graphics, Texture* texture, World* world, Map* map, bool unborn, int id) : Animal(x, y, graphics, texture, world, map, unborn, id)
{
	//use namespaces to get access to constants and enums
	using namespace AnimalEnumeration;
	using namespace AnimalConstants;

	//Spawn as unborn or a random state
	if (unborn)
	{
		animalState = ANIMAL_UNBORN;
	}
	else
	{
		const ANIMAL_STATE ANIMAL_STATES[6] = { ANIMAL_UNBORN, ANIMAL_BORN_SMALL, ANIMAL_BORN, ANIMAL_FULL_SIZE_1, ANIMAL_FULL_SIZE_2, ANIMAL_FULL_SIZE_3 };
		animalState = ANIMAL_STATES[Functions::generateRandomNumber(0, 5)];
	}

	growth = Functions::generateRandomNumber(0, 50);
	maxGrothFullSize = ANIMAL_GROWTH_RATE_FULL_SIZE_TO_DEATH_AVERAGE + Functions::generateRandomNumber(-ANIMAL_GROWTH_RATE_FULL_SIZE_TO_DEATH_AVERAGE, ANIMAL_GROWTH_RATE_FULL_SIZE_TO_DEATH_AVERAGE);
	entityName = "Chicken";
	animalType = CHICKEN;

	//set weight
	forces.weight = ANIMAL_VALUES[animalType][ANIMAL_WEIGHT];
	//maximum speed that this animal can move by "powered" by its own feet
	maximumOwnAcceleration = 0.35;
}

//Destructor
Chicken::~Chicken()
{

}

//method override
void Chicken::proceed(int framerate)
{
	growAnimal(framerate, 1);
	//Only update text if something relevant was changed before
	if (entityChanged)
	{
		updateDebugText();
		entityChanged = false;
	}
	//Do action
	handleAction(framerate);

	updateDebugTextPosition();
	calcFrame(framerate);
}

//Method override
void Chicken::growAnimal(int framerate, double rate)
{
	using namespace AnimalEnumeration;

	int growthCap[6] = { ANIMAL_GROWTH_RATE_UNBORN_TO_BORN_SMALL, ANIMAL_GROWTH_RATE_BORN_SMALL_TO_BORN, ANIMAL_GROWTH_RATE_BORN_TO_FULL_SIZE, (int)maxGrothFullSize, ANIMAL_GROWTH_RATE_FULL_SIZE_TO_DEATH_AVERAGE };
	int fullSize = 0;

	if (animalState < ANIMAL_DISAPPEARED)
	{
		//Tree increments state
		if (growthCap[animalState] <= (int)growth)
		{
			switch (animalState)
			{
			case ANIMAL_UNBORN:
				animalState = ANIMAL_BORN_SMALL;
				break;
			case ANIMAL_BORN_SMALL:
				animalState = ANIMAL_BORN;
				break;
			case ANIMAL_BORN:
				fullSize = Functions::generateRandomNumber(0, 2);
				switch (fullSize)
				{
				case 0:
					animalState = ANIMAL_FULL_SIZE_1;
					break;
				case 1:
					animalState = ANIMAL_FULL_SIZE_2;
					break;
				case 2:
					animalState = ANIMAL_FULL_SIZE_3;
					break;
				default:
					animalState = ANIMAL_FULL_SIZE_1;
					break;
				}

				break;
			case ANIMAL_FULL_SIZE_1:
			case ANIMAL_FULL_SIZE_2:
			case ANIMAL_FULL_SIZE_3:
				animalState = ANIMAL_DEAD;
				break;
			case ANIMAL_DEAD:
				animalState = ANIMAL_DISAPPEARED;
				break;
			default:
				break;
			}
		}

		//Grow the animal
		growth = growth + (rate*Functions::calculateFrameFactor(framerate));
	}

}