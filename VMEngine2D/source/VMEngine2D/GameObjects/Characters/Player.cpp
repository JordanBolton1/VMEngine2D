#include "VMEngine2D/GameObjects/Characters/Player.h"
#include "VMEngine2D/Input.h"
#include "VMEngine2D/AnimStateMachine.h"
#include"VMEngine2D/Game.h"
#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"
#include "VMEngine2D/GameObjects/Components/CollisionComponent.h"
#include "VMEngine2D/GameObjects/Projectile.h"
#include "VMEngine2D/GameState.h"
#include "VMEngine2D/GameObjects/Characters/Enemy.h"

#include "SDL2/SDL_mixer.h"

Player::Player(Vector2 StartPosition, SDL_Renderer* Renderer) :Character(StartPosition)
{
	BoostersIndex = PlayerAnims :: BOOSTERS_IDLE;
	DmgIndex = PlayerAnims::BASE_FULL;
	SheildIndex = PlayerAnims::EMPTY;
	Scale = 1.5f;
	Physics->MaxVelocity = 300.0f;
	Physics->Drag = 5.0f;
	ShootSFXIndex = 0;

	Lives = 4;

	Collision->Dimensions.Height = 42.0f;
	Collision->Dimensions.Width = 42.0f;

	Collision->Dimensions.Offset = Vector2(15.0f,15.0f);

	STAnimationData AnimData = STAnimationData();
	AnimData.FPS = 0;

	//add ship texture into animState - 0
	AddAnimation(Renderer,"Content/MainShip/Base/Base - Full health.png", AnimData);

	//add engine to ship into animState - 1
	AddAnimation(Renderer, "Content/MainShip/Engine/Base Engine.png", AnimData);

	//update animData to handle animations
	AnimData.FPS = 24;
	AnimData.MaxFrames = 3;
	AnimData.EndFrame = 2;

	//add booster idle animation to animastate - 2
	AddAnimation(Renderer, "Content/MainShip/Engine Effects/Base Engine - Idle.png", AnimData);
	
	AnimData.MaxFrames = 4;
	AnimData.EndFrame = 3;

	//update animData to handle engine powered
	AddAnimation(Renderer, "Content/MainShip/Engine Effects/Base Engine - Powering.png", AnimData);


	//Update AnimData to handle the Shield animation
	AnimData.FPS = 24;
	AnimData.MaxFrames = 12;
	AnimData.EndFrame = 11;

	//Add the Shield animation to AnimState - 4
	AddAnimation(Renderer, "Content/MainShip/Shields/Round Shield.png", AnimData);

	//Adding in the damaged variants
	AnimData.FPS = 0;
	AnimData.MaxFrames = 1;
	AnimData.EndFrame = 0;

	//Add the small damage sprite to AnimState - 5
	AddAnimation(Renderer, "Content/MainShip/Base/Base - Slight damage.png", AnimData);

	//Add the medium damage sprite to AnimState - 6
	AddAnimation(Renderer, "Content/MainShip/Base/Base - Damaged.png", AnimData);

	//Add the large damage sprite to AnimState - 7
	AddAnimation(Renderer, "Content/MainShip/Base/Base - Very damaged.png", AnimData);



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

	if (PlayerInput->IsKeyDown(SDL_SCANCODE_SPACE) && FireTimer >= 0.30f) {
		Projectile* P = new Projectile();

		P->Position = Position;
		P->Position.x += 10.0f;
		P->Position.y += 10.0f;
		P->Acceleration = 1000.0f;
		P->Direction = Vector2(0.0f, -1.0f);
		P->TargetTag = "Enemy";

		Game::GetGameInstance().GetGameStates()->GetCurrentState()->SpawnGameObject(P);

		P = new Projectile();

		P->Position = Position;
		P->Position.x += 40.0f;
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
		for (CollisionComponent* EnemyCol : Collision->GetOverLappedByTag("Enemy")) {
			
			Enemy* EnemyRef = dynamic_cast<Enemy*>(EnemyCol->GetOwner());
			//if enemy is not being destroyed

			if (!EnemyCol->GetOwner()->ShouldDestroy()&& EnemyRef !=nullptr && !EnemyRef->isDestroyed ) {
				std::cout << "KILLLLLL" << std::endl;
				//destroy enemy
				dynamic_cast<Character*>(EnemyCol->GetOwner())->RemoveLives(1);
				//remove life from player
				RemoveLives(1);
				//Check if player has shield and remove it
				if (SheildIndex = PlayerAnims::SHIELD) {
					SheildIndex = PlayerAnims::EMPTY;
				}
			}
		}
	}

	//Damage Anims
	if (Lives == 4) {
		DmgIndex = PlayerAnims::BASE_FULL;
	}

	if (Lives == 3) {
		DmgIndex = PlayerAnims::BASE_DMG1;
	}

	if (Lives == 2) {
		DmgIndex = PlayerAnims::BASE_DMG2;
	}

	if (Lives == 1) {
		DmgIndex = PlayerAnims::BASE_DMG3;
	}

	//Add Shield
	if (Collision->IsOverlappingTag("Shield")) {
		bOverlapDetected = true;

		//getting all overlapped collectibles and destroying them
		for (CollisionComponent* Sheild : Collision->GetOverLappedByTag("Shield")) {
			if (!Sheild->GetOwner()->ShouldDestroy()) {
				dynamic_cast<Character*>(Sheild->GetOwner())->RemoveLives(1);
				//Add Shield to Player so long as it is not max lives
				if (Lives != MaxLives) {
					//Check if Shield has already been applied
					if (SheildIndex = PlayerAnims::EMPTY) {
						SheildIndex = PlayerAnims::SHIELD;
					}
					AddLives(1);
				}

			}
		}
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

	//Enemy Projectile Collision
	if (Collision->IsOverlappingTag("Player")) {
		bOverlapDetected = true;

		//getting all overlapped enemy projectiles and destroying them
		for (CollisionComponent* Projectile : Collision->GetOverLappedByTag("Player")) {
			if (!Projectile->GetOwner()->ShouldDestroy()) {
				dynamic_cast<Character*>(Projectile->GetOwner())->RemoveLives(1);
				//Remove life from player
				RemoveLives(1);
				//Check if player has shield and remove it
				if (SheildIndex = PlayerAnims::SHIELD) {
					SheildIndex = PlayerAnims::EMPTY;
				}
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
	//draw engine to the screen
	CharacterAnimations->Draw(Renderer, PlayerAnims::ENGINE_BASE, Position, Rotation, Scale, bFlipped);

	//draw ship to screen
	CharacterAnimations->Draw(Renderer, DmgIndex, Position, Rotation, Scale, bFlipped);

	//Offset the shield so it lines up with the player
	Vector2 Shd_Offset = Vector2(-13.0f, -13.0f);

	//Draw and play the relevant shield animation
	CharacterAnimations->Draw(Renderer, SheildIndex, Position + Shd_Offset, Rotation, Scale, bFlipped);

	//draw booster to the screen
	CharacterAnimations->Draw(Renderer, BoostersIndex, Position, Rotation, Scale, bFlipped);


	
}

void Player::ActivateSheilds()
{
	if (SheildIndex = PlayerAnims::EMPTY) {
		SheildIndex = PlayerAnims::SHIELD;
	}
}

void Player::SetMaxLives()
{

	Lives = 5;
}
