#pragma once
#include "Renderable.h"
#include "TexturesEnumeration.h"

class Entity : 
	public Renderable
{
public:
	Entity(int x, int y, Graphics* graphics, TexturesEnumeration::TEXTURES_NAME texture, int const* FRAME_COUNT, int const* FRAME_WIDTH, int const* FRAME_HEIGHT);
	~Entity();
	virtual void render();
private:
	TexturesEnumeration::TEXTURES_NAME texture;
	int currentFrame;
	int const* FRAME_COUNT;
	int const* FRAME_WIDTH;
	int const* FRAME_HEIGHT;
};

