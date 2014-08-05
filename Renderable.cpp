//Renderable class for everything that shall be renderable
#include "Renderable.h"

//Constructor
Renderable::Renderable(int x, int y, Graphics* graphics)
{
	this->x = x;
	this->y = y;
	this->graphics = graphics;
}
//Constructor
Renderable::Renderable()
{
}

//Destructor
Renderable::~Renderable()
{
}

//abstract render function
void Renderable::render()
{

}

//Returns the x pos
int Renderable::getX()
{
	return x;
}

//Returns the y pos
int Renderable::getY()
{
	return y;
}