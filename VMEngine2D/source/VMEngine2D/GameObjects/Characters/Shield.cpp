#include "VMEngine2D/GameObjects/Characters/Shield.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"
#include "VMEngine2D/Game.h"

Shield::Shield(Vector2 StartPosition, SDL_Renderer* Renderer) : Character(StartPosition)
{
	Scale = 1.0f;
	Tag = "Shield";

	STAnimationData AnimData = STAnimationData();

	//Update AnimData to handle the Shield animation
	AnimData.FPS = 24;
	AnimData.MaxFrames = 12;
	AnimData.EndFrame = 11;

	//Add the Shield animation to AnimState - 4
	AddAnimation(Renderer, "Content/MainShip/Shields/Round Shield.png", AnimData);
}

Shield::~Shield()
{
}

void Shield::Update()
{
	//Run Parent class update first
	Character::Update();
	//check if lives are 0
	if (GetLives() == 0) {
		
		//destroy self if 0
		this->DestroyGameObject();
	}
}

void Shield::Draw(SDL_Renderer* Renderer)
{
	//draw the Shield
	CharacterAnimations->Draw(Renderer, 0, Position, Rotation, Scale, false);
}
