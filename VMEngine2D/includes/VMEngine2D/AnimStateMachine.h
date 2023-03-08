#pragma once
#include "Animation.h"
#include <iostream>
#include <vector>

class AnimStateMachine {
public:
	AnimStateMachine();
	~AnimStateMachine();

	// Add an animation to the vector array of Animations
	void AddAnimation(SDL_Renderer* Renderer, const char* SpriteSheetPath, STAnimationData AnimationData);

	// draw the animation based on the anim index via the 
	void Draw(SDL_Renderer* Renderer, unsigned int AnimIndex, Vector2 Position,double Rotation, float Scale, bool bFlip);

	std::vector<Animation*>GetAnimations() const;

private:
	//hold an array of animation objects
	std::vector<Animation*> Animations;

};
