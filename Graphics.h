#pragma once
#include "Texture.h"
#include "TexturesEnumeration.h"
#include "RenderList.h"
#include "Camera.h"

class Graphics
{
public:

	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	Graphics(Camera* camera);
	~Graphics();
	SDL_Window* getGWindow();
	SDL_Renderer* getGRenderer();
	bool initTexture(std::string path, TexturesEnumeration::TEXTURES_NAME textureName);
	void graphicsRender();
	bool drawRenderable(Renderable* renderable);
	bool drawTexture(TexturesEnumeration::TEXTURES_NAME texture, int x, int y, int w, int h);
	bool drawFrameTexture(TexturesEnumeration::TEXTURES_NAME texture, int x, int y, int currentFrame, int currentRow, const int* FRAME_WIDTH, const int* FRAME_HEIGHT);
	int getCameraX();
	int getCameraY();

private:

	Texture* gTextures[TexturesEnumeration::TEXTURES_COUNT]; //Array with all the Textures
	RenderList* toRender;
	Camera* gCamera;
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	
	bool initGraphics();
	void closeGraphics();
	
};

