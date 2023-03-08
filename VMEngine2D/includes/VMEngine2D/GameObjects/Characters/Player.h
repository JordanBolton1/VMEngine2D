#pragma once
#include "VMEngine2D/GameObjects/Character.h"

enum PlayerAnims : unsigned int {

	BASE_FULL = 0,
	ENGINE_BASE = 1,
	BOOSTERS_IDLE = 2,
	BOOSTERS_POWERING = 3,

};

class Player :
	public Character {

public :

	Player(Vector2 StartPosition, SDL_Renderer* Renderer);
	virtual ~Player();

	virtual void ProcessInput(Input* PlayerInput) override;

	virtual void Update() override;

	virtual void Draw(SDL_Renderer* Renderer) override;


protected:

	//the direction of player based on input
	Vector2 InputDir;

	//play booster animation
	unsigned int BoostersIndex;
};

