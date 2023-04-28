#include "VMEngine2D/GameStates/GameOver.h"
#include "VMEngine2D/Text.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/Input.h"
#include "VMEngine2D/GameStates/PlayState.h"


GameOverState::GameOverState(SDL_Window* Window, SDL_Renderer* Renderer) : GameState(Window, Renderer)
{
	GameOverText = nullptr;
	ScoreText = nullptr;
	RestartText = nullptr;

	BGM = Mix_LoadMUS("Content/Audio/BG_Music/Menu.wav");

	if (BGM == NULL) {
		std::cout << "menu music couldnt load" << std::endl;
	}
}

void GameOverState::BeginState()
{
	GameState::BeginState();

	Mix_VolumeMusic(25);
	//play music
	if (Mix_PlayMusic(BGM, -1) == -1) {
		std::cout << "couldnt play menu music" << std::endl;
	}

	//////GAME OVER TEXT//////
	GameOverText = new Text(StateRenderer);

	STTextInfo TextSettings;
	TextSettings.Size = 100;
	TextSettings.Position = Vector2(40.0f, 25.0f);
	TextSettings.TextStr = "GAME OVER";

	GameOverText->InitText("Content/Fonts/dogica.ttf", TextSettings);
	ActivateTextObject(GameOverText);


	///////SCORE TEXT//////
	ScoreText = new Text(StateRenderer);

	TextSettings.Size = 40;
	TextSettings.Position = Vector2(290.0f, 150.0f);
	TextSettings.TextStr = "SCORE: " + to_string(Game::GetGameInstance().GameScore);

	ScoreText->InitText("Content/Fonts/dogica.ttf",TextSettings );

	ActivateTextObject(ScoreText);


	//////RESTART TEXT//////
	RestartText = new Text(StateRenderer);

	TextSettings.Size = 24;
	TextSettings.Position = Vector2(240.0f, 250.0f);
	TextSettings.TextStr = "Press R To Restart";

	RestartText->InitText("Content/Fonts/dogica.ttf", TextSettings);

	ActivateTextObject(RestartText);
}

void GameOverState::ProcessInput(Input* PlayerInput)
{
	GameState::ProcessInput(PlayerInput);

	if (PlayerInput->IsKeyDown(SDL_SCANCODE_R)) {
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

	GameOverText = nullptr;
	ScoreText = nullptr;
	RestartText = nullptr;

	//stop and free the background music from memory
	if (BGM != nullptr) {
		Mix_HaltMusic();
		Mix_FreeMusic(BGM);
	}
}
