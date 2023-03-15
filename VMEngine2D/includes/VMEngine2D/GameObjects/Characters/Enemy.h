#pragma once
#include "VMEngine2D/GameObjects/Character.h"

enum EnemyAnims : unsigned int {
	BASE = 0,
	BOOSTERS= 1
};

class Enemy : public Character {

public: 
	Enemy(Vector2 StartPosition, SDL_Renderer*Renderer);


	virtual void Update() override;

	virtual void Draw(SDL_Renderer* Renderer) override;

private:
};