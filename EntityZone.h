#pragma once
#include <unordered_map> 

class Entity;

class EntityZone
{
public:

	EntityZone();
	~EntityZone();
	void addEntityToZone(Entity* entity, int id);
	void removeEntityFromZone(int id);
	void clearEntities();
	std::unordered_map<int, Entity*>* getEntities();
	int getZoneNumber();
	bool setZoneNumber(int zoneNumber);

private:

	std::unordered_map<int, Entity*> entities;
	int zoneNumber;

};

