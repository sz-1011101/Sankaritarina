//Renderable class for everything that shall be renderable
#include "Renderable.h"
#include "Enumeration.h"

//Constructor
Renderable::Renderable(int xPos, int yPos, Graphics* nGraphics)
{
	x = xPos;
	y = yPos;
	graphics = nGraphics;
}
//Constructor
Renderable::Renderable()
{
}

//Deconstructor
Renderable::~Renderable()
{
}

//abstract render function
void Renderable::render()
{

}