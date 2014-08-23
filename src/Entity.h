#pragma once
#include <string>

#include "Renderable.h"
#include "World.h"
#include "Map.h"
#include "EntityStruct.h"
#include "EntityEnumeration.h"

class Texture;
class EntityZone;
class Text;
class Map;
class Action;
class Controller;


class Entity : 
	public Renderable
{
public:

	const int MAX_ACCELARATION_Y = 5;

	Entity(int x, int y, Graphics* graphics, Texture* texture, World* world, int id);
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
	virtual void handleCollisions(int framerate, Map* map);
	void setAction(Action* action);
	Action* getAction();
	void push(double x, double y, int framerate, bool selfAccelerated);

	void setHeading(EntityEnumeration::ENTITY_HEADING);


protected:

	const double FRAME_TIME_RATE = 1;
	double maximumOwnAcceleration;

	Texture* texture;
	int currentFrame;
	World* world;
	Text* debugText;
	Action* action;
	EntityZone* currentEntityZone;
	std::string entityName;
	int id;
	EntityStruct::entityForces forces;
	bool entityChanged;
	EntityEnumeration::ENTITY_HEADING heading;
	double frameTime = 0;

	void updateDebugTextPosition();
	void updateDebugText();
	void handleAction(int framerate);
};

