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

	const char* GetTag() const { return Tag; }
	// set the gameobject to be destriyed in thehandle garbage function
	void DestroyGameObject() { bShouldDestroy = true; }

	//get the should dstroy bool
	bool ShouldDestroy() const { return bShouldDestroy; }
protected:
	//scale of the object
	float Scale;
	//rotaation of objerct
	double Rotation;
	//store an array of components
	ComponentStack AllComponents;

	//tag the gameobject for detection
	const char* Tag;

public:
	//screen position the gameObject
	Vector2 Position;

private:
	//if set game should destroy the object
	bool bShouldDestroy;

};