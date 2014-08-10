#pragma once
#include "Controller.h"

class Animal;

class AnimalController :
	public Controller
{
public:

	AnimalController(Animal* entity, Map* map);
	~AnimalController();
	virtual Action* decideAction(int framerate);

private:

	const int DECICION_COOLDOWN_THRESHOLD = 5;

};

