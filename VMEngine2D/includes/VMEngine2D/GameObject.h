#pragma once
#include "Vector2.h"
#include <iostream>
#include <vector>

class Input;
struct SDL_Renderer;
class Components;

typedef std::vector<Components*> ComponentStack;

class GameObject {
public:
	GameObject();
	// destructor needs to be virtual or the inherited claass destructor wont run
	virtual ~GameObject();

	//handle input detection for this gameObject
	virtual void ProcessInput(Input* PlayerInput){}

	//run logic of gameObject
	virtual void Update();

	//render the gameObject 
	virtual void Draw(SDL_Renderer* Renderer){}

	//add a component intop the cmponent stack
	void AddComponent(Components* NewComponent);

protected:
	//scale of the object
	float Scale;
	//rotaation of objerct
	double Rotation;
	//store an array of components
	ComponentStack AllComponents;

public:
	//screen position the gameObject
	Vector2 Position;

};