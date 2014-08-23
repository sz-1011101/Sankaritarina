//This class namespace enumerations for trees
#pragma once


namespace TreeEnumeration
{

	typedef enum TREES
	{
		APPLETREE = 0,
		TREES_TOTAL
	};

	typedef enum TREE_ATTRIBUTES
	{
		TREE_FRAME_WIDTH = 0,
		TREE_FRAME_HEIGHT,
		TREE_FRAME_COUNT,
		TREE_FRAME_CENTER_OFFSET,
		TREE_WEIGHT,
		TREE_ATTRIBUTES_TOTAL
	};

	typedef enum TREE_STATE
	{
		TREE_SEEDED = 0,
		TREE_SAPLING,
		TREE_BIGGER_SAPLING,
		TREE_SMALL,
		TREE_FULL_SIZE,
		TREE_DEAD,
		TREE_DISAPPEARED,
		TREE_STATE_TOTAL
	};
	typedef enum TREE_GROWTH_RATE
	{
		TREE_GROWTH_RATE_SEEDED_TO_SAPLING = 100,
		TREE_GROWTH_RATE_SAPLING_TO_BIGGER_SAPPLING = 100,
		TREE_GROWTH_RATE_BIGGER_SAPPLING_TO_SMALL = 200,
		TREE_GROWTH_RATE_SMALL_TO_FULL_SIZE = 500,
		TREE_GROWTH_RATE_FULL_SIZE_TO_DEATH_AVERAGE = 1000,
		TREE_GROWTH_RATE_DEATH_TO_DISAPPEAR = 300
	};

}