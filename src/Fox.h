#pragma once
#include "Animal.h"
class Fox :
	public Animal
{
public:

	Fox(int x, int y, Graphics* graphics, Texture* texture, World* world, Map* map, bool unborn, int id);
	~Fox();
	virtual void proceed(int framerate);
	virtual void growAnimal(int framerate, double rate);
	virtual void calcFrame(int framerate);

private:

	const int FRAME_DURATION = 5;

};

