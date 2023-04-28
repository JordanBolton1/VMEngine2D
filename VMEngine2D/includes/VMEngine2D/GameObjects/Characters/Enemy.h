#pragma once
#include "VMEngine2D/GameObjects/Character.h"

enum EnemyAnims : unsigned int {
	BASE = 0,
	BOOSTERS= 1,
	DESTROYED =2,
	BASE2 = 3,
	BOOSTERS2 = 4,
	DESTROYED2 = 5
};

class Enemy : public Character {

public: 
	Enemy(Vector2 StartPosition, SDL_Renderer*Renderer);


	virtual void Update() override;

	virtual void Draw(SDL_Renderer* Renderer) override;

public:

	bool isDestroyed;

	//Store animations for the enemy type and destruction anims
	EnemyAnims EnemyType;

	

private:

protected:

	float deathTimer;

};