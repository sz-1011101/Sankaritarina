//This class handles Animals
#include "Animal.h"
#include "Text.h"
#include "EntityZone.h"
#include "Action.h"

//Animal constructor
Animal::Animal(int x, int y, Graphics* graphics, Texture* texture, World* world, Map* map, bool unborn, int id) : Entity(x, y, graphics, texture, world, id)
{

	animalActionState = AnimalEnumeration::ANIMAL_ACTION_IDLE;

	action = NULL;
}

//Animal destructor
Animal::~Animal()
{
	//Deallocate action
	if (action != NULL)
	{
		delete action;
		action = NULL;
	}


}

//Renders the animal according to the state
void Animal::render()
{
	using namespace AnimalEnumeration;
	using namespace AnimalConstants;

	//color mod by worlds lighting
	graphics->setTextureColorMod(texture, world->getRedColorMod(), world->getGreenColorMod(), world->getBlueColorMod());
	//draw frame of the tree

	if (heading == EntityEnumeration::LEFT)
	{
		graphics->drawFrameTexture(texture, (int)x, (int)y, currentFrame, 0, ANIMAL_VALUES[animalType][ANIMAL_FRAME_WIDTH], ANIMAL_VALUES[animalType][ANIMAL_FRAME_HEIGHT], true, true);
	}
	else
	{
		graphics->drawFrameTexture(texture, (int)x, (int)y, currentFrame, 0, ANIMAL_VALUES[animalType][ANIMAL_FRAME_WIDTH], ANIMAL_VALUES[animalType][ANIMAL_FRAME_HEIGHT], true);
	}


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

//Lets animals move until they hit the ground, automatically adds gravity
void Animal::handleCollisions(int framerate, Map* map)
{

	const int FRAME_WIDTH = AnimalConstants::ANIMAL_VALUES[animalType][AnimalEnumeration::ANIMAL_FRAME_WIDTH];
	const int FRAME_HEIGHT = AnimalConstants::ANIMAL_VALUES[animalType][AnimalEnumeration::ANIMAL_FRAME_HEIGHT];
	const int FRAME_CENTER_OFFSET = AnimalConstants::ANIMAL_VALUES[animalType][AnimalEnumeration::ANIMAL_FRAME_CENTER_OFFSET];
	
	const int MAP_GROUND_HEIGHT = map->getGraphicalHeightSegment(map->getTileXFromPosition((int)x + FRAME_CENTER_OFFSET));

	if (MAP_GROUND_HEIGHT <= y + FRAME_HEIGHT)
	{
		y = MAP_GROUND_HEIGHT - FRAME_HEIGHT;
		forces.y = 0;
	}
	//Map border collision
	if (x <= 0)
	{
		x = 0;
	}
	else if (x >= map->getMapWidth()*map->MAP_TILE_WIDTH_HEIGHT - FRAME_WIDTH)
	{
		x = map->getMapWidth()*map->MAP_TILE_WIDTH_HEIGHT - FRAME_WIDTH;
	}
}

//proceed, override this to use in derived classes
void Animal::proceed(int framerate)
{
	//reset the action state
	animalActionState = AnimalEnumeration::ANIMAL_ACTION_IDLE;
}

//Animal growth, override this to use in derived classes
void Animal::growAnimal(int framerate, double rate)
{

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

//Return the animals action state it currently is in
AnimalEnumeration::ANIMAL_ACTION_STATE Animal::getActionStatus()
{
	return animalActionState;
}

//set the animals action status
void Animal::setActionStatus(AnimalEnumeration::ANIMAL_ACTION_STATE actionState)
{
	animalActionState = actionState;
}

//Returns the current state the animal is
AnimalEnumeration::ANIMAL_STATE Animal::getAnimalState()
{
	return animalState;
}