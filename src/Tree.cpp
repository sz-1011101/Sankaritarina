//This class handles trees
#include "World.h"
#include <stdio.h>

#include "Tree.h"
#include "Functions.h"
#include "Text.h"


//Tree constructor, calling superclass
Tree::Tree(int x, int y, int weight, Graphics* graphics, Texture* texture, int const* FRAME_COUNT, int const* FRAME_WIDTH, int const* FRAME_HEIGHT, int const*  FRAME_CENTER_OFFSET, World* world, bool seeded, int id) : Entity(x, y, weight, graphics, texture, FRAME_COUNT, FRAME_WIDTH, FRAME_HEIGHT, FRAME_CENTER_OFFSET, world, id)
{
	using namespace TreeEnumeration;
	//Spawn as a tiny seed or at a random size
	if (seeded)
	{
		treeState = TREE_SEEDED;
	}
	else
	{
		const TREE_STATE TREE_STATES[5] = { TREE_SEEDED, TREE_SAPLING, TREE_BIGGER_SAPLING, TREE_SMALL, TREE_FULL_SIZE };
		treeState = TREE_STATES[Functions::generateRandomNumber(0, 4)]; //Randomize tree state
	}

	growth = Functions::generateRandomNumber(0, 50);
	maxGrothFullSize = TREE_GROWTH_RATE_FULL_SIZE_TO_DEATH_AVERAGE + Functions::generateRandomNumber(-TREE_GROWTH_RATE_FULL_SIZE_TO_DEATH_AVERAGE, TREE_GROWTH_RATE_FULL_SIZE_TO_DEATH_AVERAGE);
	entityName = "Tree";
}

//Tree Destructor
Tree::~Tree()
{
}

//Renders the tree according to the 
void Tree::render()
{
	calcFrame(0); //TODO call from outside
	//color mod by worlds lighting
	graphics->setTextureColorMod(texture, world->getRedColorMod(), world->getGreenColorMod(), world->getBlueColorMod());
	//draw frame of the tree
	graphics->drawFrameTexture(texture, (int)x, (int)y, currentFrame, 0, FRAME_WIDTH, FRAME_HEIGHT, true);

}

//Calc frame of the displayed tree
void Tree::calcFrame(int framerate)
{
	using namespace TreeEnumeration;
	//Set frame according to state
	if (treeState == TREE_FULL_SIZE)
	{
		currentFrame = TREE_FULL_SIZE + world->getCurrentSeason();

	}
	else
	{
		switch (treeState)
		{
		case TREE_SEEDED:
			currentFrame = 0;
			break;
		case TREE_SAPLING:
			currentFrame = 1;
			break;
		case TREE_BIGGER_SAPLING:
			currentFrame = 2;
			break;
		case TREE_SMALL:
			currentFrame = 3;
			break;
		case TREE_FULL_SIZE:
			currentFrame = 4;
			break;
		case TREE_DEAD:
			currentFrame = 7;
			break;
		default:
			currentFrame = 4;
			break;
		}
	}
}

//Tree grows with framerate offset
void Tree::growTree(int framerate, double rate)
{
	using namespace TreeEnumeration;

	int growthCap[6] = { TREE_GROWTH_RATE_SEEDED_TO_SAPLING, TREE_GROWTH_RATE_SAPLING_TO_BIGGER_SAPPLING, TREE_GROWTH_RATE_BIGGER_SAPPLING_TO_SMALL, TREE_GROWTH_RATE_SMALL_TO_FULL_SIZE, (int)maxGrothFullSize, TREE_GROWTH_RATE_DEATH_TO_DISAPPEAR };

	if (treeState < TREE_DISAPPEARED)
	{
		//Tree increments state
		if (growthCap[treeState] <= (int)growth)
		{
			switch (treeState)
			{
			case TREE_SEEDED:
				treeState = TREE_SAPLING;
				break;
			case TREE_SAPLING:
				treeState = TREE_BIGGER_SAPLING;
				break;
			case TREE_BIGGER_SAPLING:
				treeState = TREE_SMALL;
				break;
			case TREE_SMALL:
				treeState = TREE_FULL_SIZE;
				break;
			case TREE_FULL_SIZE:
				treeState = TREE_DEAD;
				break;
			case TREE_DEAD:
				treeState = TREE_DISAPPEARED;
				break;
			}
			growth = 0;
		}
		//Tree grows
		growth = growth + (rate*Functions::calculateFrameFactor(framerate));
	}
}


//Process Tree
void Tree::proceed(int framerate)
{
	growTree(framerate, 1);
	//Only update text if something relevant was changed before
	if (entityChanged)
	{
		updateDebugText();
		entityChanged = false;
	}
	updateDebugTextPosition();

}

//Returns if this tree is dead and therefor is obsolete
bool Tree::flaggedForRemoval()
{
	if (treeState == TreeEnumeration::TREE_DISAPPEARED)
	{
		return true;
	}
	else
	{
		return false;
	}
}
