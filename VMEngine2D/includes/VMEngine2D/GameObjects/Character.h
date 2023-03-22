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

	//
	virtual void Update() override;

	//virtual allows for derived calls to overide
	//override the process input method/function in the gameobject base class
	virtual void Draw(SDL_Renderer* Renderer) override;

//add an animaition into the animaitonStateMachine
	void AddAnimation(SDL_Renderer* Renderer, const char* SpriteSheetPath, STAnimationData AnimationData);

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
};