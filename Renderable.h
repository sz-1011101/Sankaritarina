#pragma once

class Graphics; //forward declaration
 
class Renderable
{
protected:

	Graphics* graphics;
	int x;
	int y;

public:

	Renderable();
	Renderable(int x, int y, Graphics* graphics);
	~Renderable();
	virtual void render();
};

