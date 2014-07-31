#pragma once
#include "Renderable.h"
#include "Texture.h"
#include "World.h"

class Entity : 
	public Renderable
{
public:
	Entity(int x, int y, Graphics* graphics, Texture* texture, int const* FRAME_COUNT, int const* FRAME_WIDTH, int const* FRAME_HEIGHT, World* world);
	~Entity();
	virtual void render();
	virtual void calcFrame(int framerate);
	virtual void proceed(int framerate);
protected:
	Texture* texture;
	int currentFrame;
	World* world;
	int const* FRAME_COUNT;
	int const* FRAME_WIDTH;
	int const* FRAME_HEIGHT;
};

