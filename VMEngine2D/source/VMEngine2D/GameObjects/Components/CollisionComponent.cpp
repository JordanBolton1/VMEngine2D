#include "VMEngine2D/GameObjects/Components/CollisionComponent.h"
#include "VMEngine2D/GameObject.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/GameState.h"

CollisionComponent::CollisionComponent(GameObject* OwnerObject) : Components(OwnerObject)
{
	AttatchedGameState = Game::GetGameInstance().GetGameStates()->GetCurrentState();
}

CollisionComponent::~CollisionComponent()
{
	//remove self from game when deleted
	AttatchedGameState->RemoveCollisionFromGameState(this);

	for(CollisionComponent * OtherCol : OverlappedCollisions) {
		if (OtherCol->GetOwner()->ShouldDestroy()) {
			continue;
		}

		//remove self from the overlapped collisions - 
		OtherCol->RemoveCollisionFromOverlapped(this);
	}
}

void CollisionComponent::Update()
{
	//run parent class update
	Components::Update();

	//follow the position of the parent game object
	Dimensions.Position = OwnerObject->Position;

	//loop through all of the game colldier and detect intersecting collders
	for (CollisionComponent* OtherCol : Game::GetGameInstance().GetGameCollider()) {
		//skip this collision
		if (OtherCol == this) {
			continue;//continue will skip the to the next item in the array
		}

		SDL_FRect OtherRect;
		OtherRect.x = OtherCol->Dimensions.Position.x;
		OtherRect.y = OtherCol->Dimensions.Position.y;
		OtherRect.w = OtherCol->Dimensions.Width;
		OtherRect.h = OtherCol->Dimensions.Height;

		SDL_FRect ColRect;
		ColRect.x = Dimensions.Position.x;
		ColRect.y = Dimensions.Position.y;
		ColRect.w = Dimensions.Width;
		ColRect.h = Dimensions.Height;

		//check if the collider is in the overlapped collsions
		std::vector<CollisionComponent*>::iterator It = std::find(OverlappedCollisions.begin(), OverlappedCollisions.end(), OtherCol);


		//check if this collision is interceting with the other collision
		if (SDL_HasIntersectionF(&ColRect,&OtherRect)) {
			//if the other collision is not in overlapped collisons
			if (It == OverlappedCollisions.end()) {
				//addd the object into overlaapping collision
				OverlappedCollisions.push_back(OtherCol);
			}
			
		}
		else {
			
			//if the collsion in in the overlappedcoollsions
			if (It != OverlappedCollisions.end()) {
				//remove it
				OverlappedCollisions.erase(It);
			}
		}
	}
}

bool CollisionComponent::IsOverlappingAny()
{
	//return treu if the sixe of the array is larger than 0
	return OverlappedCollisions.size()>0;
}

bool CollisionComponent::IsOverlappingTag(const char* Tag)
{
	for (CollisionComponent* OverCol : OverlappedCollisions) {
		if (OverCol->GetOwner()->GetTag() == Tag) {
			return true;
		}
	}

	return false;
}

std::vector<CollisionComponent*> CollisionComponent::GetOverLappedByTag(const char* Tag)
{

	std::vector<CollisionComponent*> TaggedCollisions;

	for (CollisionComponent* OverCol : OverlappedCollisions) {
		if (OverCol->GetOwner()->GetTag() == Tag) {
			TaggedCollisions.push_back(OverCol);
		}
	}

	return TaggedCollisions;
}

void CollisionComponent::RemoveCollisionFromOverlapped(CollisionComponent* Collision)
{
	//erase the component from the overlapped collisions and resze the aarrY
	OverlappedCollisions.erase(std ::remove(OverlappedCollisions.begin(), OverlappedCollisions.end(), Collision),
		OverlappedCollisions.end());
}

void CollisionComponent::OnActivated()
{
	//add itself into the game collsion aray
	AttatchedGameState->AddCollisionToGameState(this);

	std::cout << "Colision activate" << std::endl;
}
