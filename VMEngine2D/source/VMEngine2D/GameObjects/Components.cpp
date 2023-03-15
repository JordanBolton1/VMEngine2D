#include "VMEngine2D/GameObjects/Components.h"
#include "VMEngine2D/GameObject.h"

Components::Components(GameObject* OwnerToAttatch)
{
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
