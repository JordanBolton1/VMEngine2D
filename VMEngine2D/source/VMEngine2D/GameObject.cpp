#include "VMEngine2D/GameObject.h"
#include <iostream>
GameObject::GameObject()
{
	Scale = 1.0f;
	Rotation = 0.0;
	std::cout << "game obj created"<< std::endl;
}

GameObject::~GameObject()
{
	std::cout << "game obj destroyed" << std::endl;
}
