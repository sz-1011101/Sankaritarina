//this class handles text rendering
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <algorithm>

#include "Text.h"
#include "Graphics.h"

//Constructor
Text::Text(std::string displayedText, int x, int y, int r, int g, int b, TTF_Font* font, Graphics* graphics)
{
	text = displayedText;

	SDL_Color rgbColor = { r, g, b };
	this->color = rgbColor;

	this->font = font;
	this->graphics = graphics;
	this->x = x;
	this->y = y;
	this->lineDistance = lineDistance;
	//Create the texture
	if (!initText(displayedText, color, font, graphics))
	{
		printf("Error creating text \"%s\"\n", (std::string)displayedText);
	}

}

//Destructor
Text::~Text()
{
	clearText();
}

//Deallocate
void Text::clearText()
{
	SDL_DestroyTexture(texture);
}

//Initialize the texure from provided text
bool Text::initText(std::string displayedText, SDL_Color color, TTF_Font* font, Graphics* graphics)
{
	SDL_Surface* loadedSurface = NULL;

	textWidth = 0;
	textHeight = 0;


	//Use the font of provided graphics if no own font provided
	if (font == NULL)
	{
		loadedSurface = TTF_RenderText_Blended_Wrapped(graphics->getFont(), displayedText.c_str(), color,300);
	}
	else
	{
		loadedSurface = TTF_RenderText_Blended_Wrapped(font, displayedText.c_str(), color, 300);
	}
	if (loadedSurface == NULL)
	{
		printf("Error creating surface from text \"%s\" Error: %s\n", displayedText.c_str(), SDL_GetError());
		return false;
	}
	else
	{
		//Create the texture
		texture = SDL_CreateTextureFromSurface(graphics->getGRenderer(), loadedSurface);

		//Check the last element if correct
		if (texture == NULL)
		{
			printf("Error while creating texture from surface (text) Error %s\n", SDL_GetError());
			return false;
		}

		//Set width,height
		textWidth = loadedSurface->w;
		textHeight = loadedSurface->h;

		//Free current surface
		SDL_FreeSurface(loadedSurface); 
	}

	return true;
}

//Change the text to the provided string
void Text::updateText(std::string newText)
{
	this->text = newText;
	clearText();
	initText(newText, this->color, this->font, this->graphics);
}

void Text::render()
{
	graphics->drawSDLTexture(texture, x, y, textWidth, textHeight, false); //Draw the Texture directly
}