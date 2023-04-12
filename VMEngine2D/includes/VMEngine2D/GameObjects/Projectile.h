#pragma once
#include "VMEngine2D/GameObject.h"

class AnimStateMachine;
class PhysicsComponent;
class CollisionComponent;

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


protected:
	//store main texture/anmation 
	AnimStateMachine* Animations;
	//store collisions
	CollisionComponent* Collision;
	//store the position
	PhysicsComponent* Physics;

};