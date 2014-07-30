#pragma once
#include "Renderable.h"
#include "Texture.h"

class Entity : 
	public Renderable
{
public:
	Entity(int x, int y, Graphics* graphics, Texture* texture, int const* FRAME_COUNT, int const* FRAME_WIDTH, int const* FRAME_HEIGHT);
	~Entity();
	virtual void render();
private:
	Texture* texture;
	int currentFrame;
	int const* FRAME_COUNT;
	int const* FRAME_WIDTH;
	int const* FRAME_HEIGHT;
};

