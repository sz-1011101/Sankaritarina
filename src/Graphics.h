#pragma once
#include "Texture.h"
#include "TexturesEnumeration.h"
#include "Camera.h"

class RenderVector;
class Renderable;

class Graphics
{
public:

	const int* SCREEN_WIDTH;
	const int* SCREEN_HEIGHT;

	Graphics(Camera* camera, const int* SCREEN_WIDTH, const int* SCREEN_HEIGHT);
	~Graphics();
	SDL_Window* getGWindow();
	SDL_Renderer* getGRenderer();
	TTF_Font* getFont();
	Texture* initTexture(std::string path, TexturesEnumeration::TEXTURES_NAME textureName);
	bool initFont(std::string path, int size);
	void graphicsRender();
	bool drawRenderable(Renderable* renderable, bool useCamera);
	bool drawTexture(Texture* texture, int x, int y, int w, int h, bool useCamera);
	bool drawTexture(TexturesEnumeration::TEXTURES_NAME texture, int x, int y, int w, int h, bool useCamera);
	bool drawSDLTexture(SDL_Texture* texture, int x, int y, int w, int h, bool useCamera);
	bool drawFrameTexture(Texture* texture, int x, int y, int currentFrame, int currentRow, const int* FRAME_WIDTH, const int* FRAME_HEIGHT, bool useCamera);
	bool drawFrameTexture(Texture* texture, int x, int y, int currentFrame, int currentRow, const int* FRAME_WIDTH, const int* FRAME_HEIGHT, bool useCamera, bool flippedHorizontal);
	bool drawBackground(Uint8 r, Uint8 g, Uint8 b);
	void setTextureColorMod(Texture* texture, Uint8 r, Uint8 g, Uint8 b);
	void setTextureColorMod(TexturesEnumeration::TEXTURES_NAME texture, Uint8 r, Uint8 g, Uint8 b);

	int getCameraX();
	int getCameraY();
	Texture* getTextures(TexturesEnumeration::TEXTURES_NAME texture);

private:

	Texture* gTextures[TexturesEnumeration::TEXTURES_COUNT]; /* Array with all textures,
																access this with the TEXTURES_NAMES enumeration
																after initializing the texture with initTexture(...);
																*/
	TTF_Font*  gFont = NULL;
	RenderVector* toRender;
	Camera* gCamera;
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

	bool initGraphics();
	void closeGraphics();
	bool checkRenderableVisible(Renderable* renderable);
};

