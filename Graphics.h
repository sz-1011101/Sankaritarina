#pragma once
#include "Texture.h"
#include "Enumeration.h"
#include "RenderList.h"

class Graphics
{
public:

	Graphics();
	~Graphics();
	SDL_Window* getGWindow();
	SDL_Renderer* getGRenderer();
	bool initTexture(std::string path, Enumeration::TEXTURES_NAME);
	void graphicsRender();
	bool drawRenderable(Renderable* renderable);
	bool drawTexture(Enumeration::TEXTURES_NAME texture, int x, int y, int w, int h);
	bool drawFrameTexture(Enumeration::TEXTURES_NAME texture, int x, int y, int currentFrame, const int* FRAME_WIDTH, const int* FRAME_HEIGHT);
private:
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	Texture* gTextures[Enumeration::TEXTURES_COUNT]; //Array with all the Textures
	RenderList* toRender;

	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	
	bool initGraphics();
	void closeGraphics();
	
};

