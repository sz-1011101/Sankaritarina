//This class handles Animals
#include "Animal.h"
#include "Text.h"
#include "EntityZone.h"


//Animal constructor
Animal::Animal(int x, int y, int weight, Graphics* graphics, Texture* texture, int const* FRAME_COUNT, int const* FRAME_WIDTH, int const* FRAME_HEIGHT, int const* FRAME_CENTER_OFFSET, World* world, bool unborn, int id) : Entity(x, y, weight, graphics, texture, FRAME_COUNT, FRAME_WIDTH, FRAME_HEIGHT, FRAME_CENTER_OFFSET, world, id)
{
	using namespace AnimalEnumeration;

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
	entityName = "Animal";
}

//Animal destructor
Animal::~Animal()
{
}

//Renders the animal according to the state
void Animal::render()
{
	calcFrame(0); //TODO call from outside
	//color mod by worlds lighting
	graphics->setTextureColorMod(texture, world->getRedColorMod(), world->getGreenColorMod(), world->getBlueColorMod());
	//draw frame of the tree
	graphics->drawFrameTexture(texture, x, y, currentFrame, 0, FRAME_WIDTH, FRAME_HEIGHT, true);

}

//Calculate the frame
void Animal::calcFrame(int framerate)
{
	using namespace AnimalEnumeration;

	switch (animalState)
	{
	case ANIMAL_UNBORN:
		currentFrame = 0;
		break;
	case ANIMAL_BORN_SMALL:
		currentFrame = 2;
		break;
	case ANIMAL_BORN:
		currentFrame = 2;
		break;
	case ANIMAL_FULL_SIZE_1:
		currentFrame = 4;
		break;
	case ANIMAL_FULL_SIZE_2:
		currentFrame = 6;
		break;
	case ANIMAL_FULL_SIZE_3:
		currentFrame = 8;
		break;
	default:
		currentFrame = 9;
		break;
	}

}

//Process Animal
void Animal::proceed(int framerate)
{
	growAnimal(framerate, 1);
	//Only update text if something relevant was changed before
	if (entityChanged)
	{
		updateDebugText();
		entityChanged = false;
	}
	updateDebugTextPosition();

}

void Animal::growAnimal(int framerate, double rate)
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

//Returns if this animal is dead and therefor is obsolete
bool Animal::flaggedForRemoval()
{
	if (animalState == AnimalEnumeration::ANIMAL_DISAPPEARED)
	{
		return true;
	}
	else
	{
		return false;
	}
}
