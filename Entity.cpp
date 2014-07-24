//This class handles common Entities
#include "Entity.h"
#include "Enumeration.h"
#include "Graphics.h"
#include <stdio.h>

/* Entity Cnstructor
	int xPos Postion x
	int yPos Position y
	nGraphics Graphics pointer
	nTexture texture name
	FRAME_COUNT frame amount
	FRAME_WIDTH frame width
	FRAME_HEIGHT frame height
*/
Entity::Entity(int xPos, int yPos, Graphics* nGraphics, Enumeration::TEXTURES_NAME nTexture, int const * FRAME_COUNT, int const* FRAME_WIDTH, int const* FRAME_HEIGHT)
{
	x = xPos;
	y = yPos;
	graphics = nGraphics;
	texture = nTexture;
	currentFrame = 0;
	this->FRAME_COUNT = FRAME_COUNT;
	this->FRAME_WIDTH = FRAME_WIDTH;
	this->FRAME_HEIGHT = FRAME_HEIGHT;
}

//Deconstructor
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
	graphics->drawFrameTexture(texture, x, y, currentFrame, FRAME_WIDTH, FRAME_HEIGHT);
	currentFrame++;
}