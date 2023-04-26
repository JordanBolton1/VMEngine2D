#pragma once
#include "VMEngine2D/GameObjects/Character.h"

struct Mix_Chunk;

enum PlayerAnims : unsigned int {

	BASE_FULL = 0,
	ENGINE_BASE = 1,
	BOOSTERS_IDLE = 2,
	BOOSTERS_POWERING = 3,

};

class Player : public Character {

public :

	Player(Vector2 StartPosition, SDL_Renderer* Renderer);

	virtual ~Player();

	virtual void ProcessInput(Input* PlayerInput) override;

	virtual void Update() override;

	virtual void Draw(SDL_Renderer* Renderer) override;


protected:

	//play booster animation
	unsigned int BoostersIndex;

	// store the shoot audio - max 2
	Mix_Chunk* sfx_Shoot[2] = { nullptr };

	//the shoot sound effect too lay from the array
	//unsigned int means it cant go negative
	unsigned int ShootSFXIndex;
};

