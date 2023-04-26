#include "VMEngine2D/GameObjects/Characters/Player.h"
#include "VMEngine2D/Input.h"
#include "VMEngine2D/AnimStateMachine.h"
#include"VMEngine2D/Game.h"
#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"
#include "VMEngine2D/GameObjects/Components/CollisionComponent.h"
#include "VMEngine2D/GameObjects/Projectile.h"
#include "VMEngine2D/GameState.h"

#include "SDL2/SDL_mixer.h"

Player::Player(Vector2 StartPosition, SDL_Renderer* Renderer) :Character(StartPosition)
{
	BoostersIndex = PlayerAnims :: BOOSTERS_IDLE;
	Scale = 1.5f;
	Physics->MaxVelocity = 300.0f;
	Physics->Drag = 5.0f;
	ShootSFXIndex = 0;
	Lives = 5;

	Collision->Dimensions.Height = 42.0f;
	Collision->Dimensions.Width = 42.0f;

	Collision->Dimensions.Offset = Vector2(15.0f,15.0f);

	STAnimationData AnimData1 = STAnimationData();
	AnimData1.FPS = 0;

	//add ship texture into animState - 0
	AddAnimation(Renderer,"Content/MainShip/Base/Base - Full health.png", AnimData1);

	//add engine to ship into animState - 1
	AddAnimation(Renderer, "Content/MainShip/Engine/Base Engine.png", AnimData1);

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

	if (sfx_Shoot[0] == NULL) {
		std::cout << "couldnt load audio" << std::endl;
	}
	if (sfx_Shoot[1] == NULL) {
		std::cout << "couldnt load audio" << std::endl;
	}
	sfx_Shoot[0] = Mix_LoadWAV("Content/Audio/SFX/Shoot_1.wav");
	sfx_Shoot[1] = Mix_LoadWAV("Content/Audio/SFX/Shoot_2.wav");

	//sets the volume for each chunk
	Mix_VolumeChunk(sfx_Shoot[0], 25);
}

Player::~Player()
{
	//remve audio file
	if (sfx_Shoot[0] != nullptr) {
		Mix_FreeChunk(sfx_Shoot[0]);
	}
	if (sfx_Shoot[1] != nullptr) {
		Mix_FreeChunk(sfx_Shoot[1]);
	}
	
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

	if (PlayerInput->IsKeyDown(SDL_SCANCODE_SPACE) && FireTimer >= 0.1f) {
		Projectile* P = new Projectile();

		P->Position = Position;
		P->Position.x += 15.0f;
		P->Position.y += 10.0f;
		P->Acceleration = 1000.0f;
		P->Direction = Vector2(0.0f, -1.0f);
		P->TargetTag = "Enemy";

		Game::GetGameInstance().GetGameStates()->GetCurrentState()->SpawnGameObject(P);

		P = new Projectile();

		P->Position = Position;
		P->Position.x += 45.0f;
		P->Position.y += 10.0f;
		P->Acceleration = 1000.0f;
		P->Direction = Vector2(0.0f, -1.0f);
		P->TargetTag = "Enemy";

		Game::GetGameInstance().GetGameStates()->GetCurrentState()->SpawnGameObject(P);

		FireTimer = 0.0f;

		//plays a single sfx
		//@param 1 - channel, if this is -1 it will play in the next available channel
		//@param 2 - the sfx(mixChunk*)
		//@param 3 0
		if (Mix_PlayChannel(-1, sfx_Shoot[ShootSFXIndex], 0)) {
			std::cout << "shoot sfx faled to play" << std::endl;
		}

		//increment the index by 1
		ShootSFXIndex++;

		//if the index goes 2 or highr then set back to 0 
		if (ShootSFXIndex > 1) {
			ShootSFXIndex = 0;
		}
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

	if (Collision->IsOverlappingTag("Collectable")) {
		bOverlapDetected = true;
		//getting all overlapped collectables and destroy them
		for (CollisionComponent* Collectable : Collision->GetOverLappedByTag("Collectable")) {
			//if collectable is not being destroyed
			if (!Collectable->GetOwner()->ShouldDestroy()) {
				std::cout << "Good Job!" << std::endl;
				//destroy enemy
				dynamic_cast<Character*>(Collectable->GetOwner())->RemoveLives(1);
			}
		}
	}

	else {
		bOverlapDetected = false;
	}

	float WallBot = 450.0f;
	float WallTop = 0.0f;
	float WallLeft = 0.0f;
	float WallRight = 920.0f;

	if (Position.x > WallRight) {
		Position.x = WallRight;
	}
	if (Position.x < WallLeft) {
		Position.x = WallLeft;
	}
	if (Position.y < WallTop) {
		Position.y = WallTop;
	}
	if (Position.y > WallBot) {
		Position.y = WallBot;
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
