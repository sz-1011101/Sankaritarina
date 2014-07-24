#pragma once
#include "Renderable.h"
#include "Enumeration.h"

class Entity : 
	public Renderable
{
public:
	Entity(int xPos, int yPos, Graphics* nGraphics, Enumeration::TEXTURES_NAME nTexture, int const * FRAME_COUNT, int const * FRAME_WIDTH, int const * FRAME_HEIGHT);
	~Entity();
	virtual void render();
private:
	Enumeration::TEXTURES_NAME texture;
	int currentFrame;
	int const* FRAME_COUNT;
	int const* FRAME_WIDTH;
	int const* FRAME_HEIGHT;
};

