//This class all user input
#include <stdio.h>

#include "Controls.h"
#include "ControlsEnumeration.h"
#include "Functions.h"


//Constructor, provide with a camera
Controls::Controls(Camera* camera)
{
	this->camera = camera;
}

//Destructor
Controls::~Controls()
{
}

//Procceses User Key input
ControlsEnumeration::CTRL_STATUS Controls::processKeys(ControlsEnumeration::CTRL_STATUS status, int framerate)
{
	const Uint8* currentKeys = SDL_GetKeyboardState(NULL);
	double frameFactor = Functions::calculateFrameFactor(framerate);
	//Camera movement
	if (status == ControlsEnumeration::CTRL_STATUS_MOVING_CAMERA)
	{
		//Left/Right movement of the camera
		if (currentKeys[SDL_SCANCODE_A])
		{
			camera->setCameraPos(camera->getCameraX() - (int)(camera->CAMERA_MAX_VELOCITY*frameFactor), camera->getCameraY());
		}
		else if (currentKeys[SDL_SCANCODE_D])
		{
			camera->setCameraPos(camera->getCameraX() + (int)(camera->CAMERA_MAX_VELOCITY*frameFactor), camera->getCameraY());
		}
		//Up/Down movement of the camera
		if (currentKeys[SDL_SCANCODE_W])
		{
			camera->setCameraPos(camera->getCameraX(), camera->getCameraY() - (int)(camera->CAMERA_MAX_VELOCITY*frameFactor));
		}
		else if (currentKeys[SDL_SCANCODE_S])
		{
			camera->setCameraPos(camera->getCameraX(), camera->getCameraY() + (int)(camera->CAMERA_MAX_VELOCITY*frameFactor));
		}
	}

	return status;
}

//Processes Input, returns current status
ControlsEnumeration::CTRL_STATUS Controls::processInput(ControlsEnumeration::CTRL_STATUS status, int framerate)
{
	while (SDL_PollEvent(&cEvent) != 0)
	{
		if (cEvent.type == SDL_QUIT) //Quit?
		{
			printf("Quiting now...");
			return ControlsEnumeration::CTRL_STATUS_QUIT; //"Signal" to close the programm
		}

	}
	return processKeys(status, framerate);


}
