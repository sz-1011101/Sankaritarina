#pragma once
#include "WorldEnumeration.h"

class World
{
public:
	World();
	~World();
	WorldEnumeration::WORLD_SEASONS getCurrentSeason();
private:
	WorldEnumeration::WORLD_SEASONS currentSeason = WorldEnumeration::WORLD_SEASON_SPRING;
};

