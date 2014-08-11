//This class handles Animals
#include "Animal.h"
#include "Text.h"
#include "EntityZone.h"
#include "Action.h"
#include "AnimalController.h"

//Animal constructor
Animal::Animal(int x, int y, Graphics* graphics, Texture* texture, World* world, Map* map, bool unborn, int id) : Entity(x, y, graphics, texture, world, id)
{

	animalActionState = AnimalEnumeration::ANIMAL_ACTION_IDLE;

	controller = new AnimalController(this, map); //The controller object for this entity, handles all ai interaction
	action = NULL;
}

//Animal destructor
Animal::~Animal()
{
	//Deallocate action
	if (action!=NULL)
	{
		delete action;
		action = NULL;
	}
	
	//dealloc controller object
	delete controller;
	
}

//Renders the animal according to the state
void Animal::render()
{
	calcFrame(0); //TODO call from outside
	//color mod by worlds lighting
	graphics->setTextureColorMod(texture, world->getRedColorMod(), world->getGreenColorMod(), world->getBlueColorMod());
	//draw frame of the tree
	graphics->drawFrameTexture(texture, (int)x, (int)y, currentFrame, 0, FRAME_WIDTH, FRAME_HEIGHT, true);

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

//proceed, override this to use in derived classes
void Animal::proceed(int framerate)
{
	
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