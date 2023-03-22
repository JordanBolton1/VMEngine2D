#include "VMEngine2D/GameObject.h"
#include <iostream>
#include "VMEngine2D/GameObjects/Components.h"
GameObject::GameObject()
{
	Scale = 1.0f;
	Rotation = 0.0;
	Tag = "";
	bShouldDestroy = false;


	std::cout << "game obj created"<< std::endl;
}

GameObject::~GameObject()
{
	//delete all the components from memory
	for (Components* SingleComponent : AllComponents) {
		delete SingleComponent;
	}

	//resixe the array
	AllComponents.clear();

	std::cout << "game obj destroyed" << std::endl;
}

void GameObject::Update()
{
	//update all component logic for each compinent attactched to the gameobject
	for (Components* SingleComponent : AllComponents) {
		SingleComponent->Update();
	}
}

void GameObject::AddComponent(Components* NewComponent)
{
	//make sure component is not null
	if (NewComponent != nullptr) {
		//add it to the stack
		AllComponents.push_back(NewComponent);
	}
	//error log
	else {
		std::cout << "yuh" << std::endl;
	}
}
