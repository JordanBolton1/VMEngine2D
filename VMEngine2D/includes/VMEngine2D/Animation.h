#pragma once
#include "Texture.h"

struct STAnimationData {
	unsigned int MaxFrames = 0;
	unsigned int StartFrame = 0;
	unsigned int EndFrame = 0;
	unsigned int FPS = 1;
};

class Animation {
public:
	Animation(SDL_Renderer* Renderer, const char* SpriteSheetPath, STAnimationData AnimationData);
	~Animation();

	void UpdateAnimationTimer();

	void OnFrameUpdate();

	void Draw(SDL_Renderer* Renderer, Vector2 Position, float Scale, bool bFlip);

private:
	//hold the image of the spritesheet 
	Texture* SpriteSheet;

	// hold the important animation data
	STAnimationData AnimationData;

	//this will hold the clip data for the texture
	SDL_Rect FramePos;

	//The current playing frame of the sprite sheet
	unsigned int CurrentFrame;
	//the timer to load the next frame
	double AnimationTimer;
};
