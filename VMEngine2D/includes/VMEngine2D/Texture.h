#pragma once
#include "sdl2\SDL.h"

class Vector2;


class Texture {
public:
	//functions
	Texture();
	~Texture();

	//load an image from a file path
	bool LoadImageFromFile(const char* Path, SDL_Renderer* SdlRenderer);

	//render the image to the app window
	void Draw(
		SDL_Renderer* SdlRenderer,	// @param 1 - Renderer
		Vector2 Position,			// @param 2 - The position on the screen
		SDL_Rect* SourceRect,		// @param 3 - The clip amount of the texture
		float Scale,				// @param 4 - How much to scale the image
		bool bFlip					// @param 5 - If it should flip horizontally
	);

	//get the width and height of the texture
	SDL_Rect GetDimensions() const { return TextureDimensions; }

	//Reset the texture and remove the image attatched to it
	void ResetTexture();

private:
	//variables

	//stores the dimensions of the texture
	SDL_Rect TextureDimensions;
	//Store the texture
	SDL_Texture* SdlTexture;

}; 
