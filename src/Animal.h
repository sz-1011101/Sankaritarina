#pragma once
#include "Entity.h"
#include "AnimalConstants.h"
#include "Graphics.h"
#include "Functions.h"

class Map;

class Animal :
	public Entity
{
public:

	const double MAX_MOVEMENT_ONE_STEP = 3;

	Animal(int x, int y, Graphics* graphics, Texture* texture, World* world, Map* map, bool unborn, int id);
	~Animal();
	virtual void render();
	virtual void calcFrame(int framerate);
	void growAnimal(int framerate, double rate);
	virtual void proceed(int framerate);
	virtual bool flaggedForRemoval();
	AnimalEnumeration::ANIMAL_ACTION_STATE getActionStatus();
	AnimalEnumeration::ANIMAL_STATE getAnimalState();
	void setActionStatus(AnimalEnumeration::ANIMAL_ACTION_STATE actionState);
	virtual void handleCollisions(int framerate, Map* map);

protected:

	AnimalEnumeration::ANIMAL_STATE animalState;
	AnimalEnumeration::ANIMAL_ACTION_STATE animalActionState;
	AnimalEnumeration::ANIMALS animalType;

	double growth = 0;
	double maxGrothFullSize;
	
};

