#pragma once
#include <string>

#include "Renderable.h"
#include "World.h"
#include "EntityStruct.h"

class Texture;
class EntityZone;
class Text;

class Entity : 
	public Renderable
{
public:

	Entity(int x, int y, int weight, Graphics* graphics, Texture* texture, int const* FRAME_COUNT, int const* FRAME_WIDTH, int const* FRAME_HEIGHT, World* world, int id);
	~Entity();
	virtual void render();
	virtual void calcFrame(int framerate);
	virtual void proceed(int framerate);
	virtual bool flaggedForRemoval();

	EntityZone* getCurrentEntityZone();
	void setCurrentEntityZone(EntityZone* entityZone);
	int getId();

	Text* getDebugText();
	void updateForces();

protected:

	Texture* texture;
	int currentFrame;
	World* world;
	Text* debugText;
	int const* FRAME_COUNT;
	int const* FRAME_WIDTH;
	int const* FRAME_HEIGHT;
	EntityZone* currentEntityZone;
	std::string entityName;
	int id;
	EntityStruct::entityForces forces;
	bool entityChanged;

	void updateDebugText();
	

};

