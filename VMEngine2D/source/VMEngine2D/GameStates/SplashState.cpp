#include "VMEngine2D/GameStates/SplashState.h"
#include "VMEngine2D/GameStates/PlayState.h"
#include "VMEngine2D/Text.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/Input.h"
#include "VMEngine2D/AnimStateMachine.h"

SplashState::SplashState(SDL_Window* Window, SDL_Renderer* Renderer) : GameState(Window, Renderer)
{
	SplashText = nullptr;
	AuthorText = nullptr;
	StartText = nullptr;

	SBGAnims = new AnimStateMachine();

	STAnimationData  AnimData;
	AnimData.FPS = 24;
	AnimData.MaxFrames = 9;
	AnimData.EndFrame = 8;

	SBGAnims->AddAnimation(Renderer, "Content/Background/BGStars.png", AnimData);
	SBGAnims->AddAnimation(Renderer, "Content/Background/BGStars2.png", AnimData);
	SBGAnims->AddAnimation(Renderer, "Content/Background/BGVoid.png", AnimData);
}

void SplashState::BeginState()
{
	// CREATE SPLASH TEXT //
	SplashText = new Text(StateRenderer);

	//Text Settings
	STTextInfo SplashInfo;
	SplashInfo.TextStr = "FALCON";
	SplashInfo.Size = 90;
	SplashInfo.Position = Vector2(210.0f, 50.0f);

	//intialise text
	SplashText->InitText("Content/Fonts/dogica.ttf", SplashInfo);

	//add the text to the game state
	ActivateTextObject(SplashText);

	// CREATE AUTHOR TEXT //
	AuthorText = new Text(StateRenderer);

	STTextInfo AuthorInfo;
	AuthorInfo.TextStr = "JORDAN BOLTON - 8759";
	AuthorInfo.Size = 35;
	AuthorInfo.Position = Vector2(130.0f, 200.0f);

	AuthorText->InitText("Content/Fonts/dogica.ttf", AuthorInfo);
	ActivateTextObject(AuthorText);

	// CREATE START TEXT //
	StartText = new Text(StateRenderer);

	STTextInfo StartInfo;
	StartInfo.TextStr = "PRESS ENTER TO START";
	StartInfo.Size = 20;
	StartInfo.Position = Vector2(280.0f, 400.f);

	StartText->InitText("Content/Fonts/dogica.ttf", StartInfo);
	ActivateTextObject(StartText);
}

void SplashState::ProcessInput(Input* PlayerInput)
{
	GameState::ProcessInput(PlayerInput);

	if (PlayerInput->IsKeyDown(SDL_SCANCODE_RETURN)) {
		PlayState* NewState = new PlayState(StateWindow, StateRenderer);
		Game::GetGameInstance().GetGameStates()->SwitchState(NewState);
	}
}

void SplashState::Update(float DeltaTime)
{
	GameState::Update(DeltaTime);
}

void SplashState::Draw(SDL_Renderer* Renderer)
{
	SBGAnims->Draw(Renderer, 0, Vector2::Zero(), 0.0, 1.6f, false);
	SBGAnims->Draw(Renderer, 1, Vector2::Zero(), 0.0, 1.6f, false);
	SBGAnims->Draw(Renderer, 2, Vector2::Zero(), 0.0, 1.6f, false);

	GameState::Draw(Renderer);
	
}

void SplashState::EndState()
{
	SplashText = nullptr;
	AuthorText = nullptr;
	StartText = nullptr;
}