#include "EntityZone.h"


EntityZone::EntityZone()
{
	entities.reserve(32);
}


EntityZone::~EntityZone()
{
	entities.clear();
}
