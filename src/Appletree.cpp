#include "Appletree.h"
#include "EntityConstants.h"

//Appletree constructor
Appletree::Appletree(int x, int y, Graphics* graphics, Texture* texture, World* world, bool seeded, int id) : Tree(x, y, graphics, texture, world, seeded, id)
{
	//use namespaces to get access to constants and enums
	using namespace TreeEnumeration;

	entityName = "Appletree";

	//Set the constant values (pointers)
	FRAME_WIDTH = &EntityConstants::APPLETREE_FRAME_WIDTH;
	FRAME_HEIGHT = &EntityConstants::APPLETREE_FRAME_HEIGHT;
	FRAME_COUNT = &EntityConstants::APPLETREE_FRAME_COUNT;
	FRAME_CENTER_OFFSET = &EntityConstants::APPLETREE_FRAME_CENTER_OFFSET;

	//set weight
	forces.weight = EntityConstants::APPLETREE_WEIGHT;
	MAX_OWN_ACCELERATION = &EntityConstants::APPLETREE_MAX_OWN_ACCELERATION;
}

//Destructor
Appletree::~Appletree()
{

}
