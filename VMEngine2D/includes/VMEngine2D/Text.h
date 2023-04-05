#pragma once
#include "SDL2/SDL.h"
#include "VMEngine2D/Vector2.h"
#include <iostream>
#include <string>

struct STTextInfo {
	Vector2 Position;
	Vector2 Dimensions;
	SDL_Colour Colour = {255, 255 ,255 ,255 };
	int Size = 24;
	std::string TextStr = "";
};

class Text {
public:
	Text(SDL_Renderer* Renderer);
	~Text();

	//initialise and ctrate the font using thre font supplied in the font path
	//use ther text info to posissiton, clour, size and set the text
	//dimensions will be set based on the text input
	Text* InitText(const char* FontPath, STTextInfo TextInfo);

	void Draw(SDL_Renderer* Renderer);

	//change the text in real time
	void SetText(std::string NewText);

	//move the position of the text on the screen
	void SetTextPostion(Vector2 Position);

	STTextInfo GetTextInfo() const { return TextInfo; }

private:
	STTextInfo TextInfo;
	//store the renderer
	SDL_Renderer* TextRenderer;
	//store the texture
	SDL_Texture* TextTexture;
	//store the font after resetting the text
	const char* FontPath;
};