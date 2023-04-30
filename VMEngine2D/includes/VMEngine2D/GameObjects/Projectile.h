#pragma once
#include "VMEngine2D/GameObject.h"

class AnimStateMachine;
class PhysicsComponent;
class CollisionComponent;

enum ProjAnims : unsigned int {
	PlayerProj = 0,
	EnemyProj = 1,
	EmptyProj = 2
};

class Projectile : public GameObject {

public:
	Projectile();
	virtual ~Projectile();

	virtual void Update() override;

	virtual void Draw(SDL_Renderer* Renderer) override;

	//time until death of the projectile
	float DeathTimer;

	//how fast the projectile achieves its max speeed
	float Acceleration;
	//which diection it movees in
	Vector2 Direction;

	double Rotation;

	float Scale;

	//any char that has this tag will take dmage
	const char* TargetTag;

	//Store the different projectiles
	unsigned int ProjIndex;

	//Where the projectile is fired from
	Vector2 ProjOffset;


protected:
	//store main texture/anmation 
	AnimStateMachine* Animations;
	//store collisions
	CollisionComponent* Collision;
	//store the position
	PhysicsComponent* Physics;

};