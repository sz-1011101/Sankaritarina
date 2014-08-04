#pragma once
#include "Renderable.h"
#include "World.h"

class Texture;
class EntityZone;

class Entity : 
	public Renderable
{
public:

	Entity(int x, int y, Graphics* graphics, Texture* texture, int const* FRAME_COUNT, int const* FRAME_WIDTH, int const* FRAME_HEIGHT, World* world);
	~Entity();
	virtual void render();
	virtual void calcFrame(int framerate);
	virtual void proceed(int framerate);
	virtual bool flaggedForRemoval();

	EntityZone* getCurrentEntityZone();
	void setCurrentEntityZone(EntityZone* entityZone);

	int getX();
	int getY();

protected:

	Texture* texture;
	int currentFrame;
	World* world;
	int const* FRAME_COUNT;
	int const* FRAME_WIDTH;
	int const* FRAME_HEIGHT;
	EntityZone* currentEntityZone;

};

