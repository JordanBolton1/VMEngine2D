#include "VMEngine2D/Texture.h"
#include "VMEngine2D/Vector2.h"
#include "SDL2/SDL_image.h"
#include <iostream>

using namespace std;

Texture::Texture()
{
	//initalise the texture as null
	SdlTexture = nullptr;
	//Set the texture dimensions to default (0 for everything)
	TextureDimensions = SDL_Rect();
}

Texture::~Texture()
{
	ResetTexture();

	cout << "Destroyed Textures..." << endl;
}

bool Texture::LoadImageFromFile(const char* Path, SDL_Renderer* SdlRenderer)
{
	if (SdlTexture == nullptr) {
		//load the image into a surface
		SDL_Surface* LoadedSurface = IMG_Load(Path);

		if (LoadedSurface != nullptr) {
			// create the texture from the surface
			SdlTexture = SDL_CreateTextureFromSurface(SdlRenderer, LoadedSurface);

			if (SdlTexture != nullptr) {
				cout << "Texture successfully loaded!" << endl;

				//assign the dimensions of the texture
				TextureDimensions.w = LoadedSurface->w;
				TextureDimensions.h = LoadedSurface->h;
			}
			else {
				cout << "Could not create texture from surface: " << SDL_GetError() << endl;
			}
		}
		else {
			cout << "Could not load file to surface..." << endl;
		}
	}
	else {
		//if there is already a texture - remove it then apply new texture
		ResetTexture();
		LoadImageFromFile(Path, SdlRenderer);
	}

	//return false if the texture wasn't set
	return SdlTexture != nullptr;
}

void Texture::Draw(SDL_Renderer* SdlRenderer, Vector2 Position, SDL_Rect* SourceRect, float Scale, bool bFlip)
{
	//set the rendering space and render the dimension of the texture
	// i.e. clip the texture
	SDL_Rect ClipRect = {
		//convert the float into an int
		static_cast<int>(Position.x), static_cast<int>(Position.y),
		TextureDimensions.w, TextureDimensions.h
	};

	//clip the rectangle if the source rect is updated
	if (SourceRect != nullptr) {
		//Scale the source rect if set
		ClipRect.w = SourceRect->w * Scale;
		ClipRect.h = SourceRect->h * Scale;
	}
	else {
		//This will scale if there is no source rect
		ClipRect.w *= Scale;
		ClipRect.h *= Scale;
	}

	//This will define whether or not to flip the image
	SDL_RendererFlip FlipFlag = SDL_FLIP_NONE;

	//Flip the image if bFlip is set to true
	if (bFlip) {
		FlipFlag = SDL_FLIP_HORIZONTAL;
	}

	//render the texture to the screen
	SDL_RenderCopyEx(
		SdlRenderer,		// @param1 - Renderer
		SdlTexture,			// @param2 - Texture
		SourceRect,			// @param3 - The Source rectangle
		&ClipRect,			// @Param4 - the clip amount
		0, 0,				// @param5 - angle - rotation in degrees | where the center of the image is
		FlipFlag			// @param6 - how should it flip
	);
}

void Texture::ResetTexture()
{
	if (SdlTexture != nullptr) {
		//SDL will remove the texture from memory
		SDL_DestroyTexture(SdlTexture);
		//make sure it's set to null pointer to avoid infinite loop
		SdlTexture = nullptr;
		//Reset the dimensions
		TextureDimensions = SDL_Rect();
	}
}