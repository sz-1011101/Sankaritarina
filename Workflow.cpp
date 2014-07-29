//This file contains the entry point of the application
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>     
#include <time.h>


#include "TexturesEnumeration.h"
#include "Camera.h"
#include "Graphics.h"
#include "Entity.h"
#include "Map.h"
#include "Text.h"
#include "Timer.h"

//some testing is done here
int main(int argc, char* args[])
{
	//init seed for random numbers
	srand(time(NULL));
	//Locked camera in place for now
	int const CAMERA_MAX_X = 0;
	int const CAMERA_MAX_Y = 0;

	Camera* camera = new Camera(0, 0, &CAMERA_MAX_X, &CAMERA_MAX_Y);
	Graphics* graphics = new Graphics(camera);
	Timer* fpsTimer = new Timer();
	int const FPS_LOCK = 30;
	int framerate = 0;
	int frameStartTime = 0;
	int frameEndTime = 0;
	int const MAP_WIDTH = 300;
	int const MAP_HEIGHT = 45;

	Map* myMap = new Map(graphics, &MAP_WIDTH, &MAP_HEIGHT);
	myMap->generateMap(1, 1, 20);


	bool quit = false;
	graphics->initTexture("images/GroundTileBasic16x16.png", TexturesEnumeration::TEXTURE_EARTH);
	graphics->initFont("fonts/Munro.ttf",20);

	Text* notice = new Text("This is a very early test build", 10, 680, 255, 255, 255, NULL, graphics);
	Text* fps = new Text("init fps...", 10, 700, 255, 255, 255, NULL, graphics);

	std::stringstream fps_string;

	SDL_Event e; //Event
	while (!quit)
	{
		frameStartTime = fpsTimer->getTime();
		//--------------------Start doing frame---------------------------//
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		

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

	delete graphics;
	delete myMap;
	delete camera;
	delete fpsTimer;
	delete notice;
	delete fps;
	return 0;
}