#pragma once
#include "VMEngine2D/GameObjects/Character.h" 

class Shield : public Character {
public:
	Shield(Vector2 StartPosition, SDL_Renderer* Renderer);

	virtual ~Shield();

	virtual void Update() override;

	virtual void Draw(SDL_Renderer* Renderer) override;

};