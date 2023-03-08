#pragma once
#include "Vector2.h"

class Input;
struct SDL_Renderer;

class GameObject {
public:
	GameObject();
	// destructor needs to be virtual or the inherited claass destructor wont run
	virtual ~GameObject();

	//handle input detection for this gameObject
	virtual void ProcessInput(Input* PlayerInput){}

	//run logic of gameObject
	virtual void Update(){}

	//render the gameObject 
	virtual void Draw(SDL_Renderer* Renderer){}

protected:
	//screen position the gameObject
	Vector2 Position;

	//scale of the object
	float Scale;

	//rotaation of objerct
	double Rotation;
};