#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

class Texture
{
public:

	Texture();
	~Texture();
	bool loadTexture(std::string path, SDL_Renderer* renderer);
	SDL_Texture* getTexture();
	int getTextureWidth();
	int getTextureHeight();
	void setColorModulation(Uint8 r, Uint8 g, Uint8 b);
	Uint8 getColorModR();
	Uint8 getColorModG();
	Uint8 getColorModB();

private:

	Uint8 modR;
	Uint8 modG;
	Uint8 modB;

	SDL_Texture* texture;
	int textureWidth;
	int textureHeight;
	void free();
};

