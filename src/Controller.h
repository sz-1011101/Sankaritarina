#pragma once

class Entity;
class Map;
class Action;

class Controller
{
public:

	Controller(Entity* entity, Map* map);
	~Controller();
	virtual Action* decideAction(int framerate);

protected:

	Entity* entity;
	Map* map;
	double decisionCooldown;

};

