#include "VMEngine2D/GameObjects/Characters/Enemy.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"
#include "VMEngine2D/GameObjects/Components/CollisionComponent.h"

Enemy::Enemy(Vector2 StartPosition, SDL_Renderer* Renderer) : Character (StartPosition)
{
	Tag = "Enemy";
	Scale = 1.5f;
	Rotation = 180.0;
	MovementDir = Vector2(0.0f, 1.0f);
	Physics->MaxVelocity = 300.0f;

	Collision->Dimensions.Height = 55.0f;
	Collision->Dimensions.Width = 55.0f;

	Collision->Dimensions.Offset = Vector2(20.0f, 20.0f);

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
	//call to parent function
	Character::Update();

	//more velocity down
	Physics->AddForce(MovementDir, 300.0f);

	//teleport tthe enemy back up if the reach the bottom of screen
	if (Position.y > 540.0f) {
		Position.y = -64.0f * Scale;
	}
	//if lives are 0 
	if (GetLives() == 0) {
		//add points to game
		Game::GetGameInstance().GameScore += 100;
		//destroy self
		this->DestroyGameObject();
	}
}

void Enemy::Draw(SDL_Renderer* Renderer)
{
	//draw the boposters
	CharacterAnimations->Draw(Renderer, EnemyAnims::BOOSTERS, Position, Rotation, Scale, bFlipped);
	//draw the main ship
	Character::Draw(Renderer);
}
