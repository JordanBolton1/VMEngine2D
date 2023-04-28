#include "VMEngine2D/GameObjects/Characters/Collectable.h" 
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/GameObjects/Components/CollisionComponent.h"


Collectables::Collectables(Vector2 StartPosition, SDL_Renderer* Renderer) : Character(StartPosition)
{
	Scale = 1.0f;
	Tag = "Collectable";

	Collision->Dimensions.Height = 42.0f;
	Collision->Dimensions.Width = 42.0f;

	Collision->Dimensions.Offset = Vector2(-5.0f, -5.0f);

	STAnimationData AnimData = STAnimationData();
	AnimData.FPS = 0;

	//Add the collectible to the animstate
	AddAnimation(Renderer,"Content/Collectables/Ruby.png",AnimData);
	std::cout << "collectable added" << std::endl;
	

}

Collectables::~Collectables()
{
}

void Collectables::Update()
{
	//Run Parent class update first
	Character::Update();
	//check if lives are 0
	if (GetLives() == 0) {
		//add to score
		Game::GetGameInstance().GameScore += 50;
		//destroy self if 0
		this->DestroyGameObject();
	}
}

void Collectables::Draw(SDL_Renderer* Renderer)
{
	//draw the Collectables
	CharacterAnimations->Draw(Renderer, 0, Position, Rotation, Scale, false);

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
