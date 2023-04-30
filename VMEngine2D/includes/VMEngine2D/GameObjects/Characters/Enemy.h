#pragma once
#include "VMEngine2D/GameObjects/Character.h"

enum EnemyAnims : unsigned int {
	BASE = 0,
	BASE2 = 1,
	BOOSTERS= 2,
	DESTROYED =3,
	DESTROYED2 = 4
};

class Enemy : public Character {

public: 
	Enemy(EnemyAnims EnemyType,Vector2 StartPosition, SDL_Renderer*Renderer);


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