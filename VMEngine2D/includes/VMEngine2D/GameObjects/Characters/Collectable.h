#pragma once
#include "VMEngine2D/GameObjects/Character.h" 

class Collectables : public Character {
public:
	Collectables(Vector2 StartPosition, SDL_Renderer* Renderer);

	virtual ~Collectables();

	virtual void Update() override;

	virtual void Draw(SDL_Renderer* Renderer) override;

};