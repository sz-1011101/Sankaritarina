#pragma once
#include "Entity.h"
#include "AnimalEnumeration.h"
#include "Graphics.h"
#include "Functions.h"

class Map;

class Animal :
	public Entity
{
public:

	const double MAX_MOVEMENT_ONE_STEP = 3;

	Animal(int x, int y, int weight, Graphics* graphics, Texture* texture, int const* FRAME_COUNT, int const* FRAME_WIDTH, int const* FRAME_HEIGHT, int const* FRAME_CENTER_OFFSET, World* world, Map* map, bool unborn, int id);
	~Animal();
	virtual void render();
	virtual void calcFrame(int framerate);
	void growAnimal(int framerate, double rate);
	virtual void proceed(int framerate);
	virtual bool flaggedForRemoval();
	AnimalEnumeration::ANIMAL_ACTION_STATE getActionStatus();
	void setActionStatus(AnimalEnumeration::ANIMAL_ACTION_STATE actionState);

private:

	

	AnimalEnumeration::ANIMAL_STATE animalState;
	AnimalEnumeration::ANIMAL_ACTION_STATE animalActionState;
	double growth = 0;
	double maxGrothFullSize;

};

