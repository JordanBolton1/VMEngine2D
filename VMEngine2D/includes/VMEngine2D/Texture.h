#pragma once
#include "SDL2\SDL.h"

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
		double Rotation,				// @param 3 - Rotation of the Texture
		SDL_Rect* SourceRect,		// @param 4 - The clip amount of the texture
		float Scale,				// @param 5 - How much to scale the image
		bool bFlip					// @param 6 - If it should flip horizontally
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
