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
#include "World.h"
#include "EntityControl.h"
#include "Tree.h"
#include "Animal.h"

//some testing is done here
int main(int argc, char* args[])
{
	ControlsEnumeration::CTRL_STATUS status = ControlsEnumeration::CTRL_STATUS_INIT;
	//init seed for random numbers
	srand((unsigned)time(NULL));
	int const SCREEN_WIDTH = 1280;
	int const SCREEN_HEIGHT = 720;

	int const FPS_LOCK = 999;
	int const MAP_WIDTH = 1000;
	int const MAP_HEIGHT = 200;
	int const CAMERA_MAX_X = (MAP_WIDTH - 1) * 8 - 1280;
	int const CAMERA_MAX_Y = (MAP_HEIGHT - 1) * 8 - 720;

	int framerate = 0;
	int frameStartTime = 0;
	int frameEndTime = 0;


	Camera* camera = new Camera(0, 700, &CAMERA_MAX_X, &CAMERA_MAX_Y);
	Controls* controls = new Controls(camera);
	Graphics* graphics = new Graphics(camera, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	//Init some textures
	graphics->initTexture("images/tiles/8x8/Ground_8x8.png", TexturesEnumeration::TEXTURE_EARTH);
	graphics->initTexture("images/entities/trees/appletree_64x64.png", TexturesEnumeration::TEXTURE_TREE);
	graphics->initTexture("images/entities/animals/chicken_16x8.png", TexturesEnumeration::TEXTURE_CHICKEN);
	graphics->initTexture("images/tiles/8x16/grass_tile_1_8x16.png", TexturesEnumeration::TEXTURE_GRASS_1);
	graphics->initTexture("images/world/8x8/sun_8x8.png", TexturesEnumeration::TEXTURE_SUN);

	graphics->initFont("fonts/Munro.ttf", 9); //Init font

	Timer* fpsTimer = new Timer();
	World* world = new World();
	Map* myMap = new Map(graphics, MAP_WIDTH, MAP_HEIGHT, world);

	EntityControl* entityControl = new EntityControl(myMap, graphics, world);
	Text* notice = new Text("This is a very early test build", 10, 680, 255, 255, 255, NULL, graphics,false);
	Text* fps = new Text("init fps...", 1150, 10, 255, 255, 255, NULL, graphics, false);
	Text* time = new Text("init time....", 10, 10, 255, 255, 0, NULL, graphics, false);

	myMap->generateMap(1, 1, 50, 10, entityControl); //Generate Test map
	std::stringstream fps_string;
	std::stringstream time_string;


	status = ControlsEnumeration::CTRL_STATUS_MOVING_CAMERA;
	while (status != ControlsEnumeration::CTRL_STATUS_QUIT)
	{
		frameStartTime = fpsTimer->getTime();
		//--------------------Start doing frame---------------------------//
		//Proccess Input, update status
		status = controls->processInput(status, framerate);
		world->advance(framerate);

		//Draw Map
		graphics->drawRenderable(myMap,false);

		entityControl->entityInteraction(framerate);
		//Test drawing

		graphics->drawRenderable(notice,false);
		graphics->drawRenderable(fps,false);
		graphics->drawRenderable(time,false);

		graphics->graphicsRender();
		//delay if Time left
		if (fpsTimer->getTime() - frameStartTime < 1000 / FPS_LOCK)
		{
			SDL_Delay((1000 / FPS_LOCK) - (fpsTimer->getTime() - frameStartTime)); //This seems to behave strangly sometimes

		}
		//-----------------------Done doing frame------------------------//
		frameEndTime = fpsTimer->getTime();

		//Fps counter
		framerate = 1000 / (frameEndTime - frameStartTime);
		fps_string.str("");
		fps_string << "FPS: " << framerate << " \nLocked at: " << FPS_LOCK;
		fps->updateText(fps_string.str());

		//Time display
		time->updateText(world->getTimeString());

	}

	delete camera;
	delete controls;
	delete graphics;
	delete myMap;
	delete entityControl;
	delete fpsTimer;
	delete notice;
	delete fps;

	return 0;
}