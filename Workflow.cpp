//This file contains the entry point of the application
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Graphics.h"
#include "Enumeration.h"
#include "Entity.h"


int main(int argc, char* args[])
{

	Graphics graphics;
	bool quit = false;
	graphics.initTexture("images/foo.png", Enumeration::TEXTURE_1);

	int a = 4;
	int b = 64;
	int c = 205;

	int const* FRAME_COUNT = &a;
	int const* FRAME_WIDTH = &b;
	int const* FRAME_HEIGHT = &c;


	Entity* en1 = new Entity(50,100, &graphics, Enumeration::TEXTURE_1, FRAME_COUNT, FRAME_WIDTH, FRAME_HEIGHT);
	Entity* en2 = new Entity(200, 170, &graphics, Enumeration::TEXTURE_1, FRAME_COUNT, FRAME_WIDTH, FRAME_HEIGHT);
	Entity* en3 = new Entity(60, 300, &graphics, Enumeration::TEXTURE_1, FRAME_COUNT, FRAME_WIDTH, FRAME_HEIGHT);

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

		graphics.drawRenderable(en1);
		graphics.drawRenderable(en2);
		graphics.drawRenderable(en3);

		graphics.graphicsRender();
		//SDL_Delay(1000/33);
	}
	return 0;
}