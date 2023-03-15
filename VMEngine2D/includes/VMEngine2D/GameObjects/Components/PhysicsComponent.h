#pragma once
#include "VMEngine2D/GameObjects/Components.h"
#include "VMEngine2D/Vector2.h" 
class PhysicsComponent : public Components {
public:
	PhysicsComponent(GameObject* OwnerToAttatch);

	void Update() override;

	//add accleeration in a direction multiplied by a strength force
	void AddForce(Vector2 Direction, float Force);

public:
	//CURRENT SPEED
	Vector2 Velocity;
	//max possible speed for the velocity
	float MaxVelocity;
	//how fast are we going to reach max velocity
	Vector2 Acceleration;
	//how fast the velocity decelerates
	float Drag;
};
