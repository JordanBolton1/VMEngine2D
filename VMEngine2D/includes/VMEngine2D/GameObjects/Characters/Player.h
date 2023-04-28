#pragma once
#include "VMEngine2D/GameObjects/Character.h"

struct Mix_Chunk;

enum PlayerAnims : unsigned int {

	BASE_FULL = 0,
	ENGINE_BASE = 1,
	BOOSTERS_IDLE = 2,
	BOOSTERS_POWERING = 3,
	SHIELD =4,
	BASE_DMG1 = 5,
	BASE_DMG2 = 6,
	BASE_DMG3 = 7,
	EMPTY = 8
};

class Player : public Character {

public :

	Player(Vector2 StartPosition, SDL_Renderer* Renderer);

	virtual ~Player();

	virtual void ProcessInput(Input* PlayerInput) override;

	virtual void Update() override;

	virtual void Draw(SDL_Renderer* Renderer) override;

	void ActivateSheilds();

	void SetMaxLives();


protected:

	//play booster animation
	unsigned int BoostersIndex;

	// play the correct animation for the shield
	unsigned int SheildIndex;

	//diplay damaged shp sprites
	unsigned int DmgIndex;

	//set the max amount of lives
	unsigned int MaxLives = 5;

	// store the shoot audio - max 2
	Mix_Chunk* sfx_Shoot[2] = { nullptr };

	//the shoot sound effect too lay from the array
	//unsigned int means it cant go negative
	unsigned int ShootSFXIndex;
};

