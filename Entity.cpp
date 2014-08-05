//This class handles common Entities
#include <stdio.h>

#include "Entity.h"
#include "Graphics.h"
#include "Text.h"

/* Entity Cnstructor
	int x Postion x
	int yPosition y
	graphics Graphics pointer
	texture Texture's name
	FRAME_COUNT frame amount
	FRAME_WIDTH frame width
	FRAME_HEIGHT frame height
	*/
Entity::Entity(int x, int y, Graphics* graphics, Texture* texture, int const* FRAME_COUNT, int const* FRAME_WIDTH, int const* FRAME_HEIGHT, World* world, int id) : Renderable(x, y, graphics)
{
	this->texture = texture;
	currentFrame = 0;
	this->FRAME_COUNT = FRAME_COUNT;
	this->FRAME_WIDTH = FRAME_WIDTH;
	this->FRAME_HEIGHT = FRAME_HEIGHT;
	this->world = world;
	this->id = id;
	currentEntityZone = NULL;
	debugText = new Text("Entity", x, y, 255, 255, 255, NULL, graphics, true);
}

//Destructor
Entity::~Entity()
{
	printf("Deallocating text object");
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
	currentEntityZone = entityZone;
}

//Get Debug text
Text* Entity::getDebugText()
{
	return debugText;
}

//Updates the debug text
void Entity::updateDebugText()
{

}

//returns the id of this entity
int Entity::getId()
{
	return id;
}