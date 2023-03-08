#include "VMEngine2D/GameObjects/Characters/Player.h"
#include "VMEngine2D/Input.h"
#include "VMEngine2D/AnimStateMachine.h"
#include"VMEngine2D/Game.h"

Player::Player(Vector2 StartPosition, SDL_Renderer* Renderer)
	:Character(StartPosition)
{
	BoostersIndex = PlayerAnims :: BOOSTERS_IDLE;
	Scale = 3.0f;
	MaxMoveSpeed = 500.0f;
	
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

Player::~Player()
{
}

void Player::ProcessInput(Input* PlayerInput)
{
	//set the animindex to play the first anim by default
	BoostersIndex = PlayerAnims ::BOOSTERS_IDLE;

	InputDir = Vector2::Zero();

	Rotation = 0.0;

	//update input direction
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_W)) {
		//set input y to up
		InputDir.y = -1.0;
	}
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_S)) {
		//set input y to down
		InputDir.y = 1.0;
	}
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_A)) {
		//set input x to left
		InputDir.x = -1.0;

		Rotation = -90.0;
	}
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_D)) {
		//set input x to right
		InputDir.x = 1.0;

		Rotation = 90.0;
	}
		
	if (InputDir.Length() > 0.0f) {
		BoostersIndex = PlayerAnims::BOOSTERS_POWERING;
	}

}

void Player::Update()
{
	//set the diirection based on inpput and move speed
	Vector2 Direction = InputDir.Normalised() * MaxMoveSpeed;
	//move the player basee on time
	Position += Direction * Game::GetGameInstance().GetFDeltaTime();
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
