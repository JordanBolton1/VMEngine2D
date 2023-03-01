#include "VMEngine2D/GameObject.h"
#include <iostream>
GameObject::GameObject()
{
	std::cout << "game obj created"<< std::endl;
}

GameObject::~GameObject()
{
	std::cout << "game obj destroyed" << std::endl;
}
