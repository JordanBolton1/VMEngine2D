#pragma once
#include "VMEngine2D/GameState.h"
#include "SDL2/SDL_mixer.h"

class Text;

class GameOverState : public GameState {
public:
	GameOverState(SDL_Window* Window, SDL_Renderer* Renderer);

	void BeginState()override;

	void ProcessInput(Input* PlayerInput) override;

	void Update(float DeltaTime) override;

	void Draw(SDL_Renderer* Renderer) override;

	void EndState()override;

protected:
	Text* GameOverText;

	Text* ScoreText;

	Text* RestartText;

	// store background music 
	Mix_Music* BGM;
};
