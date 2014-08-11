#pragma once
#include "Animal.h"

class Chicken :
	public Animal
{
public:
	Chicken(int x, int y, Graphics* graphics, Texture* texture, World* world, Map* map, bool unborn, int id);
	~Chicken();
	virtual void proceed(int framerate);
	virtual void growAnimal(int framerate, double rate);
};

