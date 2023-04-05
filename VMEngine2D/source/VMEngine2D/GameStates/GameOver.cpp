#include "VMEngine2D/GameStates/GameOver.h"
#include "VMEngine2D/Text.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/Input.h"
#include "VMEngine2D/GameStates/PlayState.h"


GameOverState::GameOverState(SDL_Window* Window, SDL_Renderer* Renderer) : GameState(Window, Renderer)
{
	ScoreText = nullptr;
	RestartText = nullptr;
}

void GameOverState::BeginState()
{
	GameState::BeginState();

	ScoreText = new Text(StateRenderer);
	STTextInfo TextSettings;
	TextSettings.Size = 60;
	TextSettings.Position = Vector2(440.0f, 270.0f);
	TextSettings.TextStr = to_string(Game::GetGameInstance().GameScore);

	ScoreText->InitText("Content/Fonts/dogica.ttf",TextSettings );

	ActivateTextObject(ScoreText);

	RestartText = new Text(StateRenderer);
	TextSettings.Size = 24;
	TextSettings.Position = Vector2(25.0f, 150.0f);
	TextSettings.TextStr = "Press Space To Restart";

	RestartText->InitText("Content/Fonts/dogica.ttf", TextSettings);

	ActivateTextObject(RestartText);
}

void GameOverState::ProcessInput(Input* PlayerInput)
{
	GameState::ProcessInput(PlayerInput);

	if (PlayerInput->IsKeyDown(SDL_SCANCODE_SPACE)) {
		Game::GetGameInstance().GameScore = 0;
		PlayState* NewState = new PlayState(StateWindow, StateRenderer);

		Game::GetGameInstance().GetGameStates()->SwitchState(NewState);
	}
}

void GameOverState::Update(float DeltaTime)
{
	GameState::Update(DeltaTime);
}

void GameOverState::Draw(SDL_Renderer* Renderer)
{
	GameState::Draw(Renderer);
}

void GameOverState::EndState()
{
	GameState::EndState();

	ScoreText = nullptr;
	RestartText = nullptr;
}
