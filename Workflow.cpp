//This file contains the entry point of the application
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>     
#include <time.h>

#include "TexturesEnumeration.h"
#include "Camera.h"
#include "Graphics.h"
#include "Entity.h"
#include "Map.h"



int main(int argc, char* args[])
{
	//init seed for random numbers
	srand(time(NULL));
	//Locked camera in place for now
	int const CAMERA_MAX_X = 0;
	int const CAMERA_MAX_Y = 0;

	Camera* camera = new Camera(0, 0, &CAMERA_MAX_X, &CAMERA_MAX_Y);
	Graphics* graphics = new Graphics(camera);
	
	int const MAP_WIDTH = 300;
	int const MAP_HEIGHT = 45;

	Map* myMap = new Map(graphics, &MAP_WIDTH, &MAP_HEIGHT);
	myMap->generateMap(1, 1, 20);


	bool quit = false;
	graphics->initTexture("images/GroundTileBasic16x16.png", TexturesEnumeration::TEXTURE_EARTH);


	SDL_Event e; //Event
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		graphics->drawRenderable(myMap);
		graphics->graphicsRender();
		SDL_Delay(1000/30); //improvised fps limit
	}

	graphics->~Graphics();
	myMap->~Map();
	delete camera;
	return 0;
}