#pragma once
#include "VMEngine2D/GameState.h"
#include "sdl2/SDL_mixer.h"
#include "VMEngine2D/AnimStateMachine.h"

class SplashState :
	public GameState {
public:
	SplashState(SDL_Window* Window, SDL_Renderer* Renderer);

	virtual	void BeginState() override;

	void ProcessInput(Input* PlayerInput) override;

	void Update(float DeltaTime) override;

	void Draw(SDL_Renderer* Renderer) override;

	virtual void EndState() override;

protected:
	 
	Text* SplashText;

	Text* AuthorText;

	Text* StartText;

	//background music
	Mix_Music* BGM;

	//hold the anims for background
	AnimStateMachine* SBGAnims;

};