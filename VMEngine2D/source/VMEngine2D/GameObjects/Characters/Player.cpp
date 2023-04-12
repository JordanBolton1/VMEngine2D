#include "VMEngine2D/GameObjects/Characters/Player.h"
#include "VMEngine2D/Input.h"
#include "VMEngine2D/AnimStateMachine.h"
#include"VMEngine2D/Game.h"
#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"
#include "VMEngine2D/GameObjects/Components/CollisionComponent.h"
#include "VMEngine2D/GameObjects/Projectile.h"
#include "VMEngine2D/GameState.h"

Player::Player(Vector2 StartPosition, SDL_Renderer* Renderer)
	:Character(StartPosition)
{
	BoostersIndex = PlayerAnims :: BOOSTERS_IDLE;
	Scale = 3.0f;
	Physics->MaxVelocity = 300.0f;
	Physics->Drag = 5.0f;
	Lives = 5;

	STAnimationData AnimData1 = STAnimationData();
	AnimData1.FPS = 0;


	//add ship texture into animState - 0
	AddAnimation(Renderer,
		"Content/MainShip/Base/Base - Full health.png",
		AnimData1);

	//add engine to ship into animState - 1
	AddAnimation(Renderer,
		"Content/MainShip/Engine/Base Engine.png",
		AnimData1);

	//update animData to handle animations
	AnimData1.FPS = 24;
	AnimData1.MaxFrames = 3;
	AnimData1.EndFrame = 2;

	//add booster idle animation to animastate - 2
	AddAnimation(Renderer, "Content/MainShip/Engine Effects/Base Engine - Idle.png", AnimData1);
	
	AnimData1.MaxFrames = 4;
	AnimData1.EndFrame = 3;

	//update animData to handle engine powered
	AddAnimation(Renderer, "Content/MainShip/Engine Effects/Base Engine - Powering.png",AnimData1);
}


void Player::ProcessInput(Input* PlayerInput)
{
	//set the animindex to play the first anim by default
	BoostersIndex = PlayerAnims ::BOOSTERS_IDLE;

	MovementDir = Vector2::Zero();

	Rotation = 0.0;

	//update input direction
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_W)) {
		//set input y to up
		MovementDir.y = -1.0;
	}
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_S)) {
		//set input y to down
		MovementDir.y = 1.0;
	}
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_A)) {
		//set input x to left
		MovementDir.x = -1.0;
	}
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_D)) {
		//set input x to right
		MovementDir.x = 1.0;
	}
		
	if (MovementDir.Length() > 0.0f) {
		BoostersIndex = PlayerAnims::BOOSTERS_POWERING;
	}

	static float FireTimer = 0.05f;
	FireTimer += Game::GetGameInstance().GetFDeltaTime();

	if (PlayerInput->IsKeyDown(SDL_SCANCODE_R) && FireTimer >= 0.25f) {
		Projectile* P = new Projectile();

		P->Position = Position;
		P->Position.x += 64.0f;
		P->Position.y += 64.0f;
		P->Acceleration = 1000.0f;
		P->Direction = Vector2(0.0f, -1.0f);
		P->TargetTag = "Enemy";

		Game::GetGameInstance().GetGameStates()->GetCurrentState()->SpawnGameObject(P);

		FireTimer = 0.0f;
	}
}

void Player::Update()
{
	//call o the parent funtion
	Character::Update();

	Physics->AddForce(MovementDir, 10000.0f);

	if (Collision->IsOverlappingTag("Enemy")) {
		bOverlapDetected = true;

		//getting all overlapped enemis and destroy them
		for (CollisionComponent* Enemy : Collision->GetOverLappedByTag("Enemy")) {
			//if enemy is not being destroyed
			if (!Enemy->GetOwner()->ShouldDestroy()) {
				std::cout << "KILLLLLL" << std::endl;
				//destroy enemy
				dynamic_cast<Character*>(Enemy->GetOwner())->RemoveLives(1);
				//remove life from player
				RemoveLives(1);
			}
		}
	}
	else {
		bOverlapDetected = false;
	}
}



void Player::Draw(SDL_Renderer* Renderer)
{
	

	//draw booster to the screen
	CharacterAnimations->Draw(Renderer, BoostersIndex, Position,Rotation, Scale, bFlipped);

	//make sure the draw method still runs
	Character::Draw(Renderer);

	//draw engine to the screen
	CharacterAnimations->Draw(Renderer, PlayerAnims::ENGINE_BASE, Position,Rotation, Scale, bFlipped);
}
