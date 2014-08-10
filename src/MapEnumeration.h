//This namespace handels enumerations for the Map
#pragma once

namespace MapEnumeration
{
	typedef enum MAP_TILE_TYPE
	{
		MAP_TILE_TYPE_EMTPY = 0,
		MAP_TILE_TYPE_EARTH,
		MAP_TILE_TYPE_GRASS,
		MAP_TILE_TYPE_TOTAL
	};
	typedef enum MAP_TILE_ATTRIBUTE
	{
		MAP_TILE_ATR_TYPE = 0,
		MAP_TILE_ATR_GROUND_HEIGHT ,
		MAP_TILE_ATR_TOTAL
	};
};