//This class handles camera movement and positioning
#include "Camera.h"

//Camera constructor
Camera::Camera(int x, int y, int const* CAMERA_MAX_X, int const* CAMERA_MAX_Y)
{
	this->x = x;
	this->y = y;
	this->CAMERA_MAX_X = CAMERA_MAX_X;
	this->CAMERA_MAX_Y = CAMERA_MAX_Y;
}


Camera::~Camera()
{
}

int Camera::getCameraX()
{
	return x;
}
int Camera::getCameraY()
{
	return y;
}

bool Camera::setCameraPos(int x, int y)
{
	//Check for invalid positions
	if (x<0 || x>*CAMERA_MAX_X)
	{
		return false;
	}
	else if (y<0 || y>*CAMERA_MAX_Y)
	{
		return false;
	}

	this->x = x;
	this->y = y;

	return true;
}