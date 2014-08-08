#pragma once
#include <string>

#include "Renderable.h"
#include "World.h"
#include "EntityStruct.h"

class Texture;
class EntityZone;
class Text;
class Map;

class Entity : 
	public Renderable
{
public:

	Entity(int x, int y, int weight, Graphics* graphics, Texture* texture, int const* FRAME_COUNT, int const* FRAME_WIDTH, int const* FRAME_HEIGHT, int const* FRAME_CENTER_OFFSET, World* world, int id);
	~Entity();
	virtual void render();
	virtual void calcFrame(int framerate);
	virtual void proceed(int framerate);
	virtual bool flaggedForRemoval();

	EntityZone* getCurrentEntityZone();
	void setCurrentEntityZone(EntityZone* entityZone);
	int getId();

	Text* getDebugText();
	void updateForces(int framerate);
	void handleCollisions(int framerate, Map* map);

	const int MAX_ACCELARATION_Y = 5;

protected:

	Texture* texture;
	int currentFrame;
	World* world;
	Text* debugText;
	int const* FRAME_COUNT;
	int const* FRAME_WIDTH;
	int const* FRAME_HEIGHT;
	int const* FRAME_CENTER_OFFSET;
	EntityZone* currentEntityZone;
	std::string entityName;
	int id;
	EntityStruct::entityForces forces;
	bool entityChanged;

	void updateDebugTextPosition();
	void updateDebugText();
	

};

