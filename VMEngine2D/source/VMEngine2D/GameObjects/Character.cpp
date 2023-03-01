#include"VMEngine2D/GameObjects/Character.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/Input.h"
#include <iostream>

Character::Character(Vector2 StartPosition)
{
	CharacterAnimations = new AnimStateMachine();
	AnimIndex = 0;
	MaxMoveSpeed = 150.0f;
	Scale = 2.0f;
	bFlipped = false;
	Position = StartPosition;

	std::cout << "Char created" << std::endl;
}

Character::~Character()
{
	//remove AnimStateMachine from memory
	delete CharacterAnimations;
	std::cout << "Char destroyed" << std::endl;
}

void Character::ProcessInput(Input* PlayerInput)
{

	//set the animindex to play the first anim by default
	AnimIndex = 0;
	// when holding w play second animation
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_W)) {
		AnimIndex = 1;
	}

}

void Character::Update()
{

}

void Character::Draw(SDL_Renderer* Renderer)
{
	//draw the animations for the character
	CharacterAnimations->Draw(Renderer, AnimIndex, Position, Scale, bFlipped);

}

void Character::AddAnimation(SDL_Renderer* Renderer, const char* SpriteSheetPath, STAnimationData AnimationData)
{
	//add an aniomtion to the animStateMachine using the AnimStateMachine function
	CharacterAnimations->AddAnimation(Renderer, SpriteSheetPath, AnimationData);

}
