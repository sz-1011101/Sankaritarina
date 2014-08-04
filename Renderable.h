#pragma once

class Graphics; //forward declaration
 
class Renderable
{
public:

	Renderable();
	Renderable(int x, int y, Graphics* graphics);
	~Renderable();
	virtual void render();

protected:

	Graphics* graphics;
	int x;
	int y;

};

