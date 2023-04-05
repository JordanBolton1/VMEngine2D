#include "VMEngine2D/GameObjects/Characters/Enemy.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"

Enemy::Enemy(Vector2 StartPosition, SDL_Renderer* Renderer) : Character (StartPosition)
{
	Tag = "Enemy";
	Scale = 3.0f;
	Rotation = 180.0;
	MovementDir = Vector2(0.0f, 1.0f);
	Physics->MaxVelocity = 300.0f;

	STAnimationData Animdata1 = STAnimationData();

	//add the ship
	AddAnimation(Renderer, "Content/Narian/Base/Nairan - Bomber - Base.png", Animdata1);

	//set anim data for the booster animation
	Animdata1.FPS = 24;
	Animdata1.MaxFrames = 8;
	Animdata1.EndFrame = 7;

	AddAnimation(Renderer, "Content/Narian/Engine Base/Nairan - Bomber - Engine.png", Animdata1);
}


void Enemy::Update()
{
	Character::Update();

	Physics->AddForce(MovementDir, 300.0f);

	//teleport tthe enemy back up if the reach the bottom of screen
	if (Position.y > 540.0f) {
		Position.y = -64.0f * Scale;
	}
}

void Enemy::Draw(SDL_Renderer* Renderer)
{
	//draw the boposters
	CharacterAnimations->Draw(Renderer, EnemyAnims::BOOSTERS, Position, Rotation, Scale, bFlipped);
	//draw the main ship
	Character::Draw(Renderer);
}
