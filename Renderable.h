#pragma once
#include "Enumeration.h"

class Graphics; //forward declaration
 
class Renderable
{
protected:

	Graphics* graphics;
	int x;
	int y;
	int width=0;
	int height=0;

public:

	Renderable();
	Renderable(int xPos, int yPos, Graphics* nGraphics);
	~Renderable();
	virtual void render();
};

