#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderable.h"

class Text :
	public Renderable
{
public:
	Text(std::string displayedText, int x, int y, int r, int g, int b, TTF_Font* font, Graphics* graphics);
	~Text();
	virtual void render();
	void updateText(std::string newText);
private:
	std::string text;
	SDL_Color color;
	TTF_Font* font;
	SDL_Texture* texture;
	int textWidth;
	int	textHeight;

	bool initText(std::string displayedText, SDL_Color color, TTF_Font* font, Graphics* graphics);
};

