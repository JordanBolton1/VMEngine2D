#pragma once
#include "VMEngine2D/GameObject.h"


class AnimStateMachine;
struct STAnimationData;
class PhysicsComponent;
class CollisionComponent;

class Character : public GameObject {

public:
	Character(Vector2 StartPosition);
	~Character();

	//override the parent update
	virtual void Update() override;

	//virtual allows for derived calls to overide
	//override the process input method/function in the gameobject base class
	virtual void Draw(SDL_Renderer* Renderer) override;

//add an animaition into the animaitonStateMachine
	void AddAnimation(SDL_Renderer* Renderer, const char* SpriteSheetPath, STAnimationData AnimationData);

	//get the live of the player
	unsigned int GetLives()const { return Lives; }

	//set the charactes lives
	void SetLives(unsigned int NewLives) { Lives = NewLives; }

	//incrwease health
	void AddLives(int Amount);
	//decrease lives
	void RemoveLives(int Amount);

protected:
	//store all animations
	AnimStateMachine* CharacterAnimations;

	//dir to move in
	Vector2 MovementDir;

	//animation index used by the anim sate machine
	unsigned int AnimIndex;

	//flip the animation
	bool bFlipped;
	//store a 
	PhysicsComponent* Physics;

	//store a recference
	CollisionComponent* Collision;

	//register the overlap as detected and change to green
	bool bOverlapDetected;

	bool bDebugCollision;


	unsigned int Lives;
};