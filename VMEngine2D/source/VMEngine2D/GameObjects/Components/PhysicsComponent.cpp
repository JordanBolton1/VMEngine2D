#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"
#include "VMEngine2D/GameObject.h"
#include "VMEngine2D/Game.h"
#include <iostream>

PhysicsComponent::PhysicsComponent(GameObject* OwnerToAttatch) : Components(OwnerToAttatch)
{
	MaxVelocity = 150.0f;
	Drag = 1.0f;
}


void PhysicsComponent::Update()
{

	//increase veloscity by the current aacceleration
	Velocity += Acceleration *Game ::GetGameInstance().GetFDeltaTime();

	if (Velocity.Length() > MaxVelocity) {
		Velocity = Velocity.Normalised() * MaxVelocity;
	}

	float DragScale = std::min(Drag * Game::GetGameInstance().GetFDeltaTime(), 1.0f);

	Vector2 DragVelocity = Velocity * DragScale;

	Velocity -= DragVelocity;

	//move the gameobject based on velocity
	OwnerObject->Position += Velocity * Game::GetGameInstance().GetFDeltaTime();

	//reset acceleraation each frame
	Acceleration + Vector2::Zero();
}

void PhysicsComponent::AddForce(Vector2 Direction, float Force)
{
	//normlise the direection and multiplyu it by force
	Acceleration = Direction.Normalised() * Force;
}
