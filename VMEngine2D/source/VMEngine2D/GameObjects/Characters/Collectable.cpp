#include "VMEngine2D/GameObjects/Characters/Collectable.h" 
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"
#include "VMEngine2D/Game.h"


Collectables::Collectables(Vector2 StartPosition, SDL_Renderer* Renderer) : Character(StartPosition)
{
	Scale = 5.0f;
	Tag = "Collectable";

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
}
