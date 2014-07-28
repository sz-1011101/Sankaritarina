//This class handles common Entities
#include "Entity.h"
#include "TexturesEnumeration.h"
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
Entity::Entity(int x, int y, Graphics* graphics, TexturesEnumeration::TEXTURES_NAME texture, int const* FRAME_COUNT, int const* FRAME_WIDTH, int const* FRAME_HEIGHT)
{
	this->x = x;
	this->y = y;
	this->graphics = graphics;
	this->texture = texture;
	currentFrame = 0;
	this->FRAME_COUNT = FRAME_COUNT;
	this->FRAME_WIDTH = FRAME_WIDTH;
	this->FRAME_HEIGHT = FRAME_HEIGHT;
}

//Destructor
Entity::~Entity()
{
}

//render function for Entity
void Entity::render()
{
	int frameCount = *FRAME_COUNT;
	if (currentFrame >= frameCount) {
		currentFrame = 0;
	}
	graphics->drawFrameTexture(texture, x, y, currentFrame, 0, FRAME_WIDTH, FRAME_HEIGHT);
	currentFrame++;
}