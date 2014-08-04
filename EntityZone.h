#pragma once
#include <vector>

class Entity;

class EntityZone
{
public:
	EntityZone();
	~EntityZone();
	std::vector<Entity*> entities;
};

