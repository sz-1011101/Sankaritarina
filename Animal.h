#pragma once
#include "Entity.h"
#include "AnimalEnumeration.h"
#include "Graphics.h"
#include "Functions.h"

class Animal :
	public Entity
{
public:

	Animal(int x, int y, int weight, Graphics* graphics, Texture* texture, int const* FRAME_COUNT, int const* FRAME_WIDTH, int const* FRAME_HEIGHT, World* world, bool unborn, int id);
	~Animal();
	virtual void render();
	virtual void calcFrame(int framerate);
	void growAnimal(int framerate, double rate);
	virtual void proceed(int framerate);
	virtual bool flaggedForRemoval();

private:

	AnimalEnumeration::ANIMAL_STATE animalState;
	double growth = 0;
	double maxGrothFullSize;

};

