//This file contains the entry point of the application
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>     
#include <time.h>


#include "TexturesEnumeration.h"
#include "ControlsEnumeration.h"
#include "Camera.h"
#include "Graphics.h"
#include "Entity.h"
#include "Map.h"
#include "Text.h"
#include "Timer.h"
#include "Controls.h"

//some testing is done here
int main(int argc, char* args[])
{
	ControlsEnumeration::CTRL_STATUS status = ControlsEnumeration::CTRL_STATUS_INIT;
	//init seed for random numbers
	srand(time(NULL));
	int const SCREEN_WIDTH = 1280;
	int const SCREEN_HEIGHT = 720;

	int const FPS_LOCK = 30;
	int const MAP_WIDTH = 300;
	int const MAP_HEIGHT = 100;
	int const CAMERA_MAX_X = (MAP_WIDTH-1)*16-1280;
	int const CAMERA_MAX_Y = (MAP_HEIGHT-1)*16-720;
	
	int framerate = 0;
	int frameStartTime = 0;
	int frameEndTime = 0;


	Camera* camera = new Camera(0, 700, &CAMERA_MAX_X, &CAMERA_MAX_Y);
	Controls* controls = new Controls(camera);
	Graphics* graphics = new Graphics(camera, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	graphics->initTexture("images/GroundTileBasic16x16.png", TexturesEnumeration::TEXTURE_EARTH);
	graphics->initFont("fonts/Munro.ttf", 20);

	Timer* fpsTimer = new Timer();
	Map* myMap = new Map(graphics, &MAP_WIDTH, &MAP_HEIGHT);
	Text* notice = new Text("This is a very early test build", 10, 680, 255, 255, 255, NULL, graphics);
	Text* fps = new Text("init fps...", 10, 700, 255, 255, 255, NULL, graphics);

	myMap->generateMap(1, 1, 20); //Generate Test map



	std::stringstream fps_string;

	status = ControlsEnumeration::CTRL_STATUS_MOVING_CAMERA;
	while (status != ControlsEnumeration::CTRL_STATUS_QUIT)
	{
		frameStartTime = fpsTimer->getTime();
		//--------------------Start doing frame---------------------------//
		//Proccess Input, update status
		status = controls->processInput(status, framerate);

		//Test drawing
		graphics->drawRenderable(myMap);
		graphics->drawRenderable(notice);
		graphics->drawRenderable(fps);

		graphics->graphicsRender();

		//delay if Time left
		if (fpsTimer->getTime() - frameStartTime < 1000 / FPS_LOCK)
		{
			SDL_Delay((1000 / FPS_LOCK) - (fpsTimer->getTime() - frameStartTime));
		}

		//-----------------------Done doing frame------------------------//
		frameEndTime = fpsTimer->getTime();

		//Fps counter
		framerate = 1000 / (frameEndTime - frameStartTime);
		fps_string.str("");
		fps_string << "FPS: " << framerate << " Locked at: " << FPS_LOCK;
		fps->updateText(fps_string.str());
	}

	delete camera;
	delete controls;
	delete graphics;
	delete myMap;
	delete fpsTimer;
	delete notice;
	delete fps;

	return 0;
}