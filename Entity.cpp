//This class handles common Entities
#include "Entity.h"
#include "Graphics.h"
#include <stdio.h>

/* Entity Cnstructor
	int x Postion x
	int yPosition y
	graphics Graphics pointer
	texture Texture's name
	FRAME_COUNT frame amount
	FRAME_WIDTH frame width
	FRAME_HEIGHT frame height
	*/
Entity::Entity(int x, int y, Graphics* graphics, Texture* texture, int const* FRAME_COUNT, int const* FRAME_WIDTH, int const* FRAME_HEIGHT, World* world) : Renderable(x, y, graphics)
{
	this->texture = texture;
	currentFrame = 0;
	this->FRAME_COUNT = FRAME_COUNT;
	this->FRAME_WIDTH = FRAME_WIDTH;
	this->FRAME_HEIGHT = FRAME_HEIGHT;
	this->world = world;
	currentEntityZone = NULL;
}

//Destructor
Entity::~Entity()
{
}

//render function for Entity
void Entity::render()
{
	//Dummy
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

void Entity::proceed(int framerate)
{

}

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
	currentEntityZone = entityZone;
}

//Returns the x pos
int Entity::getX()
{
	return x;
}

//Returns the y pos
int Entity::getY()
{
	return y;
}