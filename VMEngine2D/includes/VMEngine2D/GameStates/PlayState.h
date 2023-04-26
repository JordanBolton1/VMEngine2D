#pragma once
#include "VMEngine2D/GameState.h"
#include "SDL2/SDL_mixer.h"

class Text;
class Player;
class AnimStateMachine;

class PlayState : public GameState {
public:
	PlayState(SDL_Window* Window, SDL_Renderer* Renderer);

	void BeginState()override;

	void ProcessInput(Input* PlayerInput) override;

	void Update(float DeltaTime) override;

	void Draw(SDL_Renderer* Renderer) override;
	
	void EndState()override;

protected:

	Text* ScoreText;
	Text* LivesText;

	//spawn enemy timer
	double SpawnTimer;

	//time to spaw enemies 
	double SpawnTime;

	double ColSpawnTimer;

	double ColSpawnTime;

	//this will stre the player
	Player* PlayerCharacter;

	//background music
	Mix_Music* BGM;

	//hold the anims for background
	AnimStateMachine* BGAnims;
};