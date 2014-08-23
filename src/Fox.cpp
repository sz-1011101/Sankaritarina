//This class implements the fox
#include "Fox.h"
#include "Text.h"
#include "EntityZone.h"
#include "Action.h"
#include "AnimalController.h"

//Constructor
Fox::Fox(int x, int y, Graphics* graphics, Texture* texture, World* world, Map* map, bool unborn, int id) : Animal(x, y, graphics, texture, world, map, unborn, id)
{

	using namespace AnimalEnumeration;
	using namespace AnimalConstants;

	//No lifecycle yet
	animalState = ANIMAL_FULL_SIZE_1;

	entityName = "Fox";
	animalType = FOX;

	//Set weight
	forces.weight = ANIMAL_VALUES[animalType][ANIMAL_WEIGHT];
	//maximum speed that this animal can move by "powered" by its own feet
	maximumOwnAcceleration = 1;
}

//Destructor
Fox::~Fox()
{

}

//override
void Fox::growAnimal(int framerate, double rate)
{
	//TODO Implement lifecycle once avaible
}

//override method
void Fox::proceed(int framerate)
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

//Calculate the current frame
void Fox::calcFrame(int framerate)
{
	using namespace AnimalEnumeration;

	switch (animalActionState)
	{
	case ANIMAL_ACTION_IDLE:
		currentFrame = 3;
		break;
	case ANIMAL_ACTION_MOVING:
		if (frameTime > FRAME_DURATION)
		{

			//Walking animation
			/*TODO The animation frames provided are not very noticable.
			Use "standing" frame as second walking frame until fixed */
			if (currentFrame == 0)
			{
				frameTime = 0;
				currentFrame = 3;
			}
			else if (currentFrame == 3)
			{
				frameTime = 0;
				currentFrame = 0;
			}
			else //Reset if other frame
			{
				frameTime = 0;
				currentFrame = 0;
			}
		}
		else
		{
			frameTime = frameTime + FRAME_TIME_RATE* Functions::calculateFrameFactor(framerate);
		}
		break;
	default:
		currentFrame = 3;
		break;
	}
}