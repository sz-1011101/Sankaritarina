//This class handles common Entities
#include <stdio.h>

#include "Entity.h"
#include "Graphics.h"
#include "Text.h"
#include "EntityZone.h"
#include "Map.h"
#include "Functions.h"

/* Entity Cnstructor
	int x Postion x
	int yPosition y
	graphics Graphics pointer
	texture Texture's name
	FRAME_COUNT frame amount
	FRAME_WIDTH frame width
	FRAME_HEIGHT frame height
	*/
Entity::Entity(int x, int y, int weight, Graphics* graphics, Texture* texture, int const* FRAME_COUNT, int const* FRAME_WIDTH, int const* FRAME_HEIGHT, int const* FRAME_CENTER_OFFSET, World* world, int id) : Renderable(x, y, graphics)
{
	this->texture = texture;
	currentFrame = 0;
	this->FRAME_COUNT = FRAME_COUNT;
	this->FRAME_WIDTH = FRAME_WIDTH;
	this->FRAME_HEIGHT = FRAME_HEIGHT;
	this->FRAME_CENTER_OFFSET = FRAME_CENTER_OFFSET;
	this->world = world;
	this->id = id;
	currentEntityZone = NULL;
	debugText = new Text("Entity", x, y - 100, 255, 255, 255, NULL, graphics, true);
	forces = { 0, 0, weight };
}

//Destructor
Entity::~Entity()
{
	delete debugText;
}

//render function for Entity
void Entity::render()
{
	//Dummy - just loops through
	int frameCount = *FRAME_COUNT;
	if (currentFrame >= frameCount) {
		currentFrame = 0;
	}

	graphics->drawFrameTexture(texture, x, y, currentFrame, 0, FRAME_WIDTH, FRAME_HEIGHT, true);
	currentFrame++;
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
		debugText->setTextPos(x, y - 50); //Update the position to the trees position
	}
}

void Entity::updateDebugTextPosition()
{
	debugText->setTextPos(x, y - 100);
}

//returns the id of this entity
int Entity::getId()
{
	return id;
}

//Update forces like gravity
//TODO x forces
void Entity::updateForces(int framerate)
{

	y = y + forces.y;

}

void Entity::handleCollisions(int framerate, Map* map)
{
	const int MAP_GROUND_HEIGHT = map->getGraphicalHeightSegment(map->getTileXFromPosition(x + *FRAME_CENTER_OFFSET));

	//if entity is in the sky, apply gravity, otherwise stop entity from falling through
	if (MAP_GROUND_HEIGHT > y + *FRAME_HEIGHT)
	{
		if (forces.y < MAX_ACCELARATION_Y)
		{
			forces.y = forces.y + 0.1*Functions::calculateFrameFactor(framerate);
		}
	}
	else
	{
		y = MAP_GROUND_HEIGHT - *FRAME_HEIGHT;
		forces.y = 0;
	}
}