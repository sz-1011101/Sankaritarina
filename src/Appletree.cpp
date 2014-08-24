#include "Appletree.h"

//Appletree constructor
Appletree::Appletree(int x, int y, Graphics* graphics, Texture* texture, World* world, bool seeded, int id) : Tree(x, y, graphics, texture, world, seeded, id)
{
	//use namespaces to get access to constants and enums
	using namespace TreeEnumeration;
	using namespace TreeConstants;

	entityName = "Appletree";
	treeType = APPLETREE;
	//set weight
	forces.weight = TREE_VALUES[treeType][TREE_WEIGHT];
	maximumOwnAcceleration = 0;
}

//Destructor
Appletree::~Appletree()
{

}
