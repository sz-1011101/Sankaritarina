//This class namespace enumerations for trees
#pragma once


namespace TreeEnumeration
{
	typedef enum TREE_STATUS
	{
		TREE_SEEDED = 0,
		TREE_SAPLING,
		TREE_BIGGER_SAPLING,
		TREE_SMALL,
		TREE_FULL_SIZE,
		TREE_STATUS_TOTAL
	};
	typedef enum TREE_GROWTH_RATE
	{
		TREE_GROWTH_RATE_SEEDED_TO_SAPLING = 100,
		TREE_GROWTH_RATE_SAPLING_TO_BIGGER_SAPPLING = 100,
		TREE_GROWTH_RATE_BIGGER_SAPPLING_TO_SMALL = 200,
		TREE_GROWTH_RATE_SMALL_TO_FULL_SIZE = 500,
	};
	//TREE_STATUS& operator++(TREE_STATUS& t)
	//{
	//	return t = TREE_STATUS((t + 1) % TREE_STATUS_TOTAL);
	//}

	//TREE_STATUS operator++(TREE_STATUS& t, int)
	//{
	//	TREE_STATUS old = t;
	//	++t;
	//	return old;
	//}
}