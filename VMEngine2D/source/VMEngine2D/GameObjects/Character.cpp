#include"VMEngine2D/GameObjects/Character.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"
#include <iostream>

Character::Character(Vector2 StartPosition)
{
	CharacterAnimations = new AnimStateMachine();
	AnimIndex = 0;
	bFlipped = false;
	Position = StartPosition;

	//create a new physics Component and store it
	Physics = new PhysicsComponent(this);

	std::cout << "Char created" << std::endl;
}

Character::~Character()
{
	//remove AnimStateMachine from memory
	delete CharacterAnimations;
	std::cout << "Char destroyed" << std::endl;
}

void Character::Update()
{
	GameObject::Update();
}



void Character::Draw(SDL_Renderer* Renderer)
{
	//draw the animations for the character
	CharacterAnimations->Draw(Renderer, AnimIndex, Position,Rotation, Scale, bFlipped);

}

void Character::AddAnimation(SDL_Renderer* Renderer, const char* SpriteSheetPath, STAnimationData AnimationData)
{
	//add an aniomtion to the animStateMachine using the AnimStateMachine function
	CharacterAnimations->AddAnimation(Renderer, SpriteSheetPath, AnimationData);

}
