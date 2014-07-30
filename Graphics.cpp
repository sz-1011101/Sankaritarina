//This class handles the Graphics, Renderer etc.
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

#include "Texture.h"
#include "Graphics.h"
#include "TexturesEnumeration.h"
#include "RenderList.h"



//Constructor of the Graphics class, provided with a camera object
Graphics::Graphics(Camera* camera, const int* SCREEN_WIDTH, const int* SCREEN_HEIGHT)
{
	this->SCREEN_WIDTH = SCREEN_WIDTH;
	this->SCREEN_HEIGHT = SCREEN_HEIGHT;
	initGraphics();
	//Initialize Texture objects
	for (int i = 0; i < TexturesEnumeration::TEXTURES_COUNT; i++)
	{
		gTextures[i] = new Texture();
	}
	this->gCamera = camera;
}

//Closing
void Graphics::closeGraphics()
{
	//Remove all the textures from the textures array
	for (int i = 0; i < TexturesEnumeration::TEXTURES_COUNT; i++)
	{
		SDL_DestroyTexture(gTextures[i]->getTexture());
	}

	//Destroy and null renderer and Window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	TTF_CloseFont(gFont);
	gWindow = NULL;
	gRenderer = NULL;
	gFont = NULL;
	//Quit SDL and IMG
	IMG_Quit();
	SDL_Quit();
}

//Init the Graphics and SDL2
bool Graphics::initGraphics()
{

	printf("Initializing Graphics...\n");

	toRender = new RenderList; //Initialize Render List

	//Print Error if not successful
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Error while init. Graphics: %s\n", SDL_GetError());
		return false;
	}

	//continue creating Window
	gWindow = SDL_CreateWindow("Sankaritarina 0.001", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, *SCREEN_WIDTH, *SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (gWindow == NULL) //Something went wrong
	{
		printf("Error while creating Window: %s\n", SDL_GetError());
		return false;
	}

	//continue creating Renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

	if (gRenderer == NULL)
	{
		printf("Error while creating Renderer: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//continue initializing IMG
	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags)) {
		printf("Error while init. SDL_image: %s\n", IMG_GetError());
		return false;
	}
	//continue with init. TFF
	if (TTF_Init() < 0)
	{
		printf("Error initializing TTF! Error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

//Initialize a font
bool Graphics::initFont(std::string path, int size)
{
	if (gFont != NULL)
	{
		TTF_CloseFont(gFont);
	}
	gFont = TTF_OpenFont(path.c_str(), size);
	if (gFont == NULL)
	{
		printf("Error initualizing font! Error: %s\n", TTF_GetError());
		return false;
	}
	return true;
}

//Initialize a Texture into the array gTexture and returns a pointer to said Texture
Texture* Graphics::initTexture(std::string path, TexturesEnumeration::TEXTURES_NAME textureName)
{
	if (!(gTextures[textureName]->loadTexture(path, gRenderer)))
	{
		printf("Error while init. Texture: %s\n", path.c_str());
		return false;
	}
	return gTextures[textureName];
}

//Destructor
Graphics::~Graphics()
{
	closeGraphics();
}

//Getter for gWindow
SDL_Window* Graphics::getGWindow()
{
	return gWindow;
}

//Getter for gRenderer
SDL_Renderer* Graphics::getGRenderer()
{
	return gRenderer;
}

TTF_Font*  Graphics::getFont()
{
	return gFont;
}

//Renders everything
void Graphics::graphicsRender()
{
	SDL_SetRenderDrawColor(gRenderer, 200, 255, 255, 0x00); //black color
	SDL_RenderClear(gRenderer);

	RenderListNode* node = toRender->getFirst();
	while (node != NULL) { //Iterate through the list
		node->getRenderable()->render(); //Render renderables
		node = node->getNext(); //next node
		toRender->removeFirst(); //remove the head of the list
	}

	//Update screen
	SDL_RenderPresent(gRenderer);
}

//Renders the provided Texture
//TODO make w,h useful
bool Graphics::drawTexture(Texture* texture, int x, int y, int w, int h, bool useCamera)
{
	if (texture != NULL)
	{
		int mWidth = texture->getTextureWidth();
		int mHeight = texture->getTextureHeight();

		//Cube with the position, width and height
		SDL_Rect rSquare;

		//Add camera offset if wanted
		if (useCamera)
		{
			rSquare = { x - gCamera->getCameraX(), y - gCamera->getCameraY(), mWidth, mHeight };
		}
		else
		{
			rSquare = { x, y, mWidth, mHeight };
		}

		SDL_RenderCopy(gRenderer, texture->getTexture(), NULL, &rSquare);
	}
	return true;
}

//Renders a texture from the gTexture array, if the texture isn't empty, return true
//TODO make w,h useful
bool Graphics::drawTexture(TexturesEnumeration::TEXTURES_NAME texture, int x, int y, int w, int h, bool useCamera)
{
	if (texture != TexturesEnumeration::TEXTURE_EMPTY)
	{
		int mWidth = gTextures[texture]->getTextureWidth();
		int mHeight = gTextures[texture]->getTextureHeight();

		//Cube with the position, width and height
		SDL_Rect rSquare;

		//Add camera offset if wanted
		if (useCamera)
		{
			rSquare = { x - gCamera->getCameraX(), y - gCamera->getCameraY(), mWidth, mHeight };
		}
		else
		{
			rSquare = { x, y, mWidth, mHeight };
		}

		SDL_RenderCopy(gRenderer, gTextures[texture]->getTexture(), NULL, &rSquare);
		return true;
	}
	return false;
}

//Renders a SDL_texture, if the texture isn't NULL, return true
//TODO make w,h useful
bool Graphics::drawSDLTexture(SDL_Texture* texture, int x, int y, int w, int h, bool useCamera)
{
	if (texture != NULL)
	{
		//Cube with the position, width and height
		SDL_Rect rSquare;

		//Add camera offset if wanted
		if (useCamera)
		{
			rSquare = { x - gCamera->getCameraX(), y - gCamera->getCameraY(), w, h };
		}
		else
		{
			rSquare = { x, y, w, h };
		}

		SDL_RenderCopy(gRenderer, texture, NULL, &rSquare);

		return true;
	}
	return false;
}

//Renders a texture from the gTexture array which is clipped in Frames
bool Graphics::drawFrameTexture(Texture* texture, int x, int y, int currentFrame, int currentRow, const int* FRAME_WIDTH, const int* FRAME_HEIGHT, bool useCamera)
{
	if (texture != NULL)
	{
		//Cube with the position, width and height
		SDL_Rect rSquare;

		//Add camera offset if wanted
		if (useCamera)
		{
			rSquare = { x - gCamera->getCameraX(), y - gCamera->getCameraY(), *FRAME_WIDTH, *FRAME_HEIGHT };
		}
		else
		{
			rSquare = { x, y, *FRAME_WIDTH, *FRAME_HEIGHT };
		}

		SDL_Rect rClip = { (currentFrame*(*FRAME_WIDTH)), 0, *FRAME_WIDTH, *FRAME_HEIGHT }; //Get the frame position and clip it

		SDL_RenderCopy(gRenderer, texture->getTexture(), &rClip, &rSquare);

		return true;
	}

	return false;
}



//Adds the Renderable object to the RenderList, to draw with graphicsRender()
bool Graphics::drawRenderable(Renderable* renderable)
{
	if (renderable != NULL) {
		toRender->addRenderable(renderable);
		return true;
	}

	return false;
}

//Retruns the Cameras X Position
int Graphics::getCameraX()
{
	return gCamera->getCameraX();
}

//Retruns the Cameras Y Position
int Graphics::getCameraY()
{
	return gCamera->getCameraY();
}