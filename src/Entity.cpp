//This class handles common Entities
#include <stdio.h>

#include "Entity.h"
#include "Graphics.h"
#include "Text.h"
#include "EntityZone.h"
#include "Functions.h"
#include "Action.h"

/* Entity Cnstructor
	int x Postion x
	int yPosition y
	graphics Graphics pointer
	texture Texture's name
	FRAME_COUNT frame amount
	FRAME_WIDTH frame width
	FRAME_HEIGHT frame height
	*/
Entity::Entity(int x, int y, Graphics* graphics, Texture* texture, World* world, int id) : Renderable(x, y, graphics)
{
	this->texture = texture;
	currentFrame = 0;
	this->world = world;
	this->id = id;
	currentEntityZone = NULL;
	debugText = new Text("Entity", x, y - 100, 255, 255, 255, NULL, graphics, true);
	forces = { 0, 0, 1 };
	heading = EntityEnumeration::RIGHT;
	frameTime = 0;

}

//Destructor
Entity::~Entity()
{
	delete debugText;
}

//render function for Entity
void Entity::render()
{

}

//Calc Frame if animation wanted
void Entity::calcFrame(int framerate)
{

}

//Entity processing
void Entity::proceed(int framerate)
{
	updateDebugTextPosition();
}

//Return if flagged for removal
bool Entity::flaggedForRemoval()
{
	return false;
}

//Gets current zone that the entity holds
EntityZone* Entity::getCurrentEntityZone()
{
	return currentEntityZone;
}

//Sets the current zone for this entity
void Entity::setCurrentEntityZone(EntityZone* entityZone)
{
	entityChanged = true; //Entity changed
	currentEntityZone = entityZone;
}

//Get Debug text
Text* Entity::getDebugText()
{
	return debugText;
}

//Updates the debug text
//Updates the debug text for this animal
void Entity::updateDebugText()
{
	std::stringstream debugStream;
	debugStream.str("");

	if (currentEntityZone != NULL)
	{
		debugStream << "id:" << id << " " << entityName << "\n" << "Zone: " << currentEntityZone->getZoneNumber();
		debugText->updateText(debugStream.str()); //Update the text
		debugText->setTextPos((int)x, (int)y - 50); //Update the position to the trees position
	}
}

void Entity::updateDebugTextPosition()
{
	debugText->setTextPos((int)x, (int)y - 100);
}

//returns the id of this entity
int Entity::getId()
{
	return id;
}

//Handle collisions....
void Entity::handleCollisions(int framerate, Map* map)
{

}

//Update forces like gravity
void Entity::updateForces(int framerate)
{
	const double FORCES_FALLDOWN = 0.1;
	const double FRAME_FACTOR = Functions::calculateFrameFactor(framerate);
	const double FORCE_DELTA = FORCES_FALLDOWN*FRAME_FACTOR;

	const double GRAVITY = 0.5;

	//Update positions by forces
	x = x + forces.x*FRAME_FACTOR;
	y = y + forces.y*FRAME_FACTOR;

	//if entity is in the sky, apply gravity
	if (forces.y < MAX_ACCELARATION_Y)
	{
		forces.y = forces.y + GRAVITY*FRAME_FACTOR;
	}

	//Update x forces
	if (forces.x > 0)
	{
		forces.x = forces.x - FORCE_DELTA;
	}
	else if (forces.x < 0)
	{
		forces.x = forces.x + FORCE_DELTA;
	}

	//Update y forces
	if (forces.y > 0)
	{
		forces.y = forces.y - FORCE_DELTA;
	}
	else if (forces.y < 0)
	{
		forces.y = forces.y + FORCE_DELTA;
	}

	//Catch jittering
	if (forces.y <= FORCE_DELTA && forces.y >= (-1)*FORCE_DELTA)
	{
		forces.y = 0;
	}
	if (forces.x <= FORCE_DELTA && forces.x >= (-1)*FORCE_DELTA)
	{
		forces.x = 0;
	}



}


//Sets the current Action of this entity
void Entity::setAction(Action* action)
{
	this->action = action;
}

//Returns the current action
Action* Entity::getAction()
{
	return action;
}

//Move the the entity in the direction provided
void Entity::push(double x, double y, int framerate, bool selfAccelerated)
{
	//const double FRAME_FACTOR = Functions::calculateFrameFactor(framerate);
	const double FRAME_FACTOR = 0.3;

	//Check if more acceleration allowed for this entity
	if (selfAccelerated && forces.x < maximumOwnAcceleration && forces.x>(-1)* maximumOwnAcceleration)
	{
		forces.x = forces.x + x*FRAME_FACTOR;
	}
	//Same as above for y-dir
	if (selfAccelerated && forces.y < maximumOwnAcceleration && forces.y>(-1)* maximumOwnAcceleration)
	{
		forces.y = forces.y + y*FRAME_FACTOR;
	}
}

//action processing
void Entity::handleAction(int framerate)
{
	if (action != NULL)
	{
		action->process(framerate);
		if (action->isActionDone())
		{
			delete action;
			action = NULL;
		}
	}
}

//Set the heading of this entity
void Entity::setHeading(EntityEnumeration::ENTITY_HEADING heading)
{
	this->heading = heading;
}