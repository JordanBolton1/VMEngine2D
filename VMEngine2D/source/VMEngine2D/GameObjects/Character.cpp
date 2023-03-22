#include"VMEngine2D/GameObjects/Character.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"
#include "VMEngine2D/GameObjects/Components/CollisionComponent.h"
#include <iostream>

Character::Character(Vector2 StartPosition)
{
	CharacterAnimations = new AnimStateMachine();
	AnimIndex = 0;
	bFlipped = false;
	Position = StartPosition;
	bOverlapDetected = false;
	bDebugCollision = true;

	//create a new physics Component and store it
	Physics = new PhysicsComponent(this);

	//create new collsion component and store it
	Collision = new CollisionComponent(this);

	//resize colliders
	Collision->Dimensions.Width = 120.0f;
	Collision->Dimensions.Height = 120.0f;

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
	if (bDebugCollision) {
		//draw trhe collision
		if (bOverlapDetected) {
			//this will  draw green
			SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 255);
		}
		else {
			//this will  draw red
			SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
		}

		//convert dimensions into an sdl_frect
		SDL_FRect ColRect = {
			Collision->Dimensions.Position.x,
			Collision->Dimensions.Position.y,
			Collision->Dimensions.Width,
			Collision->Dimensions.Height,
		};

		//drw the collider
		SDL_RenderDrawRectF(Renderer, &ColRect);
	}
	

}

void Character::AddAnimation(SDL_Renderer* Renderer, const char* SpriteSheetPath, STAnimationData AnimationData)
{
	//add an aniomtion to the animStateMachine using the AnimStateMachine function
	CharacterAnimations->AddAnimation(Renderer, SpriteSheetPath, AnimationData);

}
