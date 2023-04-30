#include "VMEngine2D/GameObjects/Characters/Enemy.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"
#include "VMEngine2D/GameObjects/Components/CollisionComponent.h"
#include "VMEngine2D/GameObjects/Projectile.h"
#include "VMEngine2D/GameState.h"

Enemy::Enemy(EnemyAnims EnemyType, Vector2 StartPosition, SDL_Renderer* Renderer) : Character (StartPosition)
{
	Tag = "Enemy";
	this->EnemyType = EnemyType;
	Scale = 1.5f;
	Rotation = 180.0;
	MovementDir = Vector2(0.0f, 1.0f);
	Physics->MaxVelocity = 300.0f;
	isDestroyed = false;
	deathTimer = 0.5f;

	Collision->Dimensions.Height = 55.0f;
	Collision->Dimensions.Width = 55.0f;

	Collision->Dimensions.Offset = Vector2(20.0f, 20.0f);

	STAnimationData Animdata = STAnimationData();
	Animdata.FPS = 0;
	//add the ship
	AddAnimation(Renderer, "Content/Narian/Base/Nairan - Bomber - Base.png", Animdata);

	//add the ship
	AddAnimation(Renderer, "Content/Narian/Base/Nairan - Fighter - Base.png", Animdata);

	//set anim data for the booster animation
	Animdata.FPS = 24;
	Animdata.MaxFrames = 8;
	Animdata.EndFrame = 7;

	AddAnimation(Renderer, "Content/Narian/Engine Base/Nairan - Bomber - Engine.png", Animdata);

	//add destruction animation
	Animdata.FPS = 24;
	Animdata.MaxFrames = 16;
	Animdata.EndFrame = 15;

	AddAnimation(Renderer, "Content/Narian/Destruction/Nairan - Bomber -  Destruction.png", Animdata);
	
	//add destruction animation
	Animdata.FPS = 24;
	Animdata.MaxFrames = 15;
	Animdata.EndFrame = 14;

	AddAnimation(Renderer, "Content/Narian/Destruction/Nairan - Fighter -  Destruction.png", Animdata);


}


void Enemy::Update()
{
	//call to parent function
	Character::Update();

	//more velocity down
	if (!isDestroyed) {
		Physics->AddForce(MovementDir, 300.0f);
	}

	//teleport tthe enemy back up if the reach the bottom of screen
	if (Position.y > 540.0f) {
		Position.y = -64.0f * Scale;
	}
	//if lives are 0 
	if (GetLives() == 0) {

		if (!isDestroyed) {

			//add points to game
			Game::GetGameInstance().GameScore += 100;
			isDestroyed = true;
			AnimIndex = EnemyAnims::DESTROYED;
			Physics->Velocity = Vector2::Zero();
			Physics->Acceleration = Vector2::Zero();
		}

		if (isDestroyed) {
			deathTimer -= Game::GetGameInstance().GetFDeltaTime();
			if (deathTimer <= 0.0f) {
				//destroy self
				this->DestroyGameObject();
			}

		}
	}

	//Fire a projectile if not destroyed already
	if (EnemyType == EnemyAnims::BASE2 && isDestroyed == false) {
		//how long the enemy has to wait in-between shots
		static float FireTimer = 3.0f;
		FireTimer += Game::GetGameInstance().GetFDeltaTime();

		if (FireTimer > 3.0f) {
			//Fire Projectile
			Projectile* E = new Projectile();

			//Setting up neccessary information
			E->Position = Position;
			E->Position.x += 14.0f;
			E->Position.y += 60.0f;
			E->Rotation = 180.0f;
			E->Acceleration = 1000.0f;
			E->Direction = Vector2(0.0f, 1.0f);
			E->TargetTag = "Player";

			//Spawning Projectile
			Game::GetGameInstance().GetGameStates()->GetCurrentState()->SpawnGameObject(E);
			std::cout << "enemy projectile spawned" << std::endl;
			//Reset Firing Timer
			FireTimer = 0.0f;
		}

		else
		{
			std::cout << "enemy projectile failed" << std::endl;
		}
	}

}

	

void Enemy::Draw(SDL_Renderer* Renderer)
{
	//draw the enemy
	if (isDestroyed != true) {
		CharacterAnimations->Draw(Renderer, EnemyType, Position, Rotation, Scale, bFlipped);

		//draw the boosters
		CharacterAnimations->Draw(Renderer, EnemyAnims::BOOSTERS, Position, Rotation, Scale, bFlipped);

	}
	else {
		//Check the enemy type and play the appropriate destruction animation
		if (EnemyType == EnemyAnims::BASE) {
			CharacterAnimations->Draw(Renderer, EnemyAnims::DESTROYED, Position, Rotation, Scale, bFlipped);
		}
		else if (EnemyType == EnemyAnims::BASE2) {
			CharacterAnimations->Draw(Renderer, EnemyAnims::DESTROYED2, Position, Rotation, Scale, bFlipped);
		}
		
	}
}
