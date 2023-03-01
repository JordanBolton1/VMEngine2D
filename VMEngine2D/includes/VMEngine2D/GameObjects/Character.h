#pragma once
#include "VMEngine2D/GameObject.h"


class AnimStateMachine;
struct STAnimationData;

class Character : public GameObject {

public:
	Character(Vector2 StartPosition);
	~Character();

	//override the process input method/function in the gameobject base class
	virtual void ProcessInput(Input* PlayerInput) override;

	virtual void Update();

	virtual void Draw(SDL_Renderer* Renderer) override;

//add an animaition into the animaitonStateMachine
	void AddAnimation(SDL_Renderer* Renderer, const char* SpriteSheetPath, STAnimationData AnimationData);

protected:
	//store all animations
	AnimStateMachine* CharacterAnimations;

	//animation index used by the anim sate machine
	unsigned int AnimIndex;

	//scale of the object
	float Scale;

	//flip the animation
	bool bFlipped;

	//maximum velocity/speed
	float MaxMoveSpeed;


};