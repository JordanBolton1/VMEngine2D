#pragma once
#include "VMEngine2D/GameObjects/Components.h"
#include "VMEngine2D/Vector2.h"
#include <iostream>
#include <vector>

class GameState;

struct STColDimensions {
	float Width = 25.0f;
	float Height = 25.0f;
	Vector2 Position;
};

class CollisionComponent : public Components {

public: 
	CollisionComponent(GameObject* OwnerObject);
	~CollisionComponent();

	void Update() override;

	//return if any collision is overlapping
	bool IsOverlappingAny();

	//return true if collision is overlapping gameobject with tag
	bool IsOverlappingTag(const char* Tag);

	//return gameobjects this collision is overlapping with this tag
	std::vector<CollisionComponent*> GetOverLappedByTag(const char* Tag);

	//remove a collider from the overlapped collisions
	void RemoveCollisionFromOverlapped(CollisionComponent* Collision);

protected:
	//
	void OnActivated() override;

public:

	//Dimension and position for the collision
	STColDimensions Dimensions;

	//store the colliders thate are being overlapped
	std::vector<CollisionComponent*> OverlappedCollisions;

private:

	//this is the game state that the collision spawn into
	GameState* AttatchedGameState;
};