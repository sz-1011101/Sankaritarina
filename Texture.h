#pragma once
#include <SDL.h>
#include <SDL_image.h>
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
private:
	SDL_Texture* texture;
	int textureWidth;
	int textureHeight;
	void free();
};

