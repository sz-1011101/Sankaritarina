#pragma once
#ifdef _MSC_VER
#include <SDL.h>
#else //Linux
#include <SDL2/SDL.h>
#endif

#include "ControlsEnumeration.h"
#include "Camera.h"

class Controls
{
public:
	Controls(Camera* camera);
	~Controls();
	ControlsEnumeration::CTRL_STATUS processInput(ControlsEnumeration::CTRL_STATUS status, int framerate);
private:
	SDL_Event cEvent;
	Camera* camera;
	ControlsEnumeration::CTRL_STATUS processKeys(ControlsEnumeration::CTRL_STATUS status, int framerate);
};

