#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/Vector2.h"

AnimStateMachine::AnimStateMachine()
{

}

AnimStateMachine::~AnimStateMachine()
{

}

void AnimStateMachine::AddAnimation(SDL_Renderer* Renderer, const char* SpriteSheetPath, STAnimationData AnimationData)
{
	//create an animation
	Animation* NewAnim = new Animation(Renderer, SpriteSheetPath, AnimationData);

	//add it into the Animations array
	Animations.push_back(NewAnim);
}

void AnimStateMachine::Draw(SDL_Renderer* Renderer, unsigned int AnimIndex, Vector2 Position,double Rotation, float Scale, bool bFlip)
{
	//make sure there is an item in the array at that index
	if (Animations.size() > AnimIndex && Animations[AnimIndex] != nullptr) {
		//draw the correct animations based on the index
		Animations[AnimIndex]->Draw(Renderer, Position,Rotation, Scale, bFlip);
	}
}

std::vector<Animation*> AnimStateMachine::GetAnimations() const
{
	return std::vector<Animation*>();
}