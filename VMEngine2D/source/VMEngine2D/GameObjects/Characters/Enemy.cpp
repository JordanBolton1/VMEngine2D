#include "VMEngine2D/GameObjects/Characters/Enemy.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/Game.h"

Enemy::Enemy(Vector2 StartPosition, SDL_Renderer* Renderer) : Character (StartPosition)
{
	Scale = 3.0f;
	Direction = Vector2(0.0f, 1.0f);
	Rotation = 180.0;

	STAnimationData Animdata1 = STAnimationData();

	//add the ship
	AddAnimation(Renderer, "Content/Narian/Base/Nairan - Bomber - Base.png", Animdata1);

	//set anim data for the booster animation
	Animdata1.FPS = 24;
	Animdata1.MaxFrames = 8;
	Animdata1.EndFrame = 7;

	AddAnimation(Renderer, "Content/Narian/Engine Base/Nairan - Bomber - Engine.png", Animdata1);
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Vector2 MoveDir = Direction * MaxMoveSpeed;
	//move the enemy based the on the movedir
	Position += MoveDir * Game::GetGameInstance().GetFDeltaTime();

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
