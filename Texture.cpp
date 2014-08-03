//This class handles Textures
#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

//Constructor of the Texture Class
Texture::Texture()
{
	//Init Texture with null
	SDL_Texture* texture = NULL;
	textureWidth = 0;
	textureHeight = 0;
	modR = 255;
	modG = 255;
	modB = 255;
}

//Destructor of the Texture Class
Texture::~Texture()
{
	free();
}

//Deallocation
void Texture::free()
{
	//Remove texture if necessary
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);

		texture = NULL;
		textureWidth = 0;
		textureHeight = 0;
	}
}

/* Loads the Texture
	path: path to texture
	renderer: corresponding renderer
	*/
bool Texture::loadTexture(std::string path, SDL_Renderer* renderer)
{
	free();
	//Load Texture from path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Error loading image from %s, Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}
	else
	{
		//Create the Texture from Surface loadedSurface
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		//Check if correct
		if (texture == NULL)
		{
			printf("Error creating Texture from %s, Error: %s\n", path.c_str(), SDL_GetError());
			return false;
		}

		//Set width,height
		textureWidth = loadedSurface->w;
		textureHeight = loadedSurface->h;

		SDL_FreeSurface(loadedSurface); //Remove the Surface
	}
	return true;
}

//get Texture
SDL_Texture* Texture::getTexture()
{
	return texture;
}

//get the textures width
int Texture::getTextureWidth()
{
	return textureWidth;
}

//get the textures height
int Texture::getTextureHeight()
{
	return textureHeight;
}

//Sets the color Modulation of this texture
void Texture::setColorModulation(Uint8 r, Uint8 g, Uint8 b)
{
	modR = r;
	modG = g;
	modB = b;
	//Set Color Modulation
	SDL_SetTextureColorMod(texture,  modR, modG, modB);
}

/*
Color mod getters
*/
Uint8 Texture::getColorModR()
{
	return modR;
}
Uint8 Texture::getColorModG()
{
	return modG;
}
Uint8 Texture::getColorModB()
{
	return modB;
}