#include "Tree.h"
#include "Functions.h"
#include "World.h"
#include <stdio.h>

//Tree constructor, calling superclass
Tree::Tree(int x, int y, Graphics* graphics, Texture* texture, int const* FRAME_COUNT, int const* FRAME_WIDTH, int const* FRAME_HEIGHT, World* world) : Entity(x, y, graphics, texture, FRAME_COUNT, FRAME_WIDTH, FRAME_HEIGHT, world)
{
	treeState = TreeEnumeration::TREE_SEEDED; //Tree begins seeded for now
}

//Tree Destructor
Tree::~Tree()
{
}

//Renders the tree according to the 
void Tree::render()
{
	calcFrame(0); //TODO call from outside
	//draw frame of the tree
	graphics->drawFrameTexture(texture, x, y, currentFrame, 0, FRAME_WIDTH, FRAME_HEIGHT, true);
}

//Calc frame of the displayed tree
void Tree::calcFrame(int framerate)
{
	using namespace TreeEnumeration;
	if (treeState == TREE_FULL_SIZE)
	{
		currentFrame = TREE_STATUS_TOTAL + world->getCurrentSeason();
		//Set frame according to status
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
	if (treeState < TREE_FULL_SIZE)
	{
		int growthCap[4] = { TREE_GROWTH_RATE_SEEDED_TO_SAPLING, TREE_GROWTH_RATE_SAPLING_TO_BIGGER_SAPPLING, TREE_GROWTH_RATE_BIGGER_SAPPLING_TO_SMALL, TREE_GROWTH_RATE_SMALL_TO_FULL_SIZE };

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
}