#include "VMEngine2D/GameObjects/Components.h"
#include "VMEngine2D/GameObject.h"

Components::Components(GameObject* OwnerToAttatch)
{
	bHasActivated = false;
// set the gameobject that ownns this compionent and save it
	OwnerObject = OwnerToAttatch;
	//attache this component to the owner game object
	OwnerObject->AddComponent(this);
}

Components::~Components()
{
	if (OwnerObject != nullptr) {
		OwnerObject = nullptr;
	}
}

void Components::Update()
{
	//check if component has been activated
	//if not then set it to activatedf and run the activated function
	//this will only run once per spawn
	if (!bHasActivated) {
		bHasActivated = true;
		OnActivated();
	}
}
