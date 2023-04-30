#include "VMEngine2D/GameObjects/Projectile.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/GameObjects/Components/CollisionComponent.h"
#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/GameState.h"
#include "VMEngine2D/GameObjects/Character.h"

Projectile::Projectile()
{
	DeathTimer = 10.0f;
	Acceleration = 1000.0f;
	Direction = Vector2::Zero();
	Rotation = 0.0;
	Scale = 1.0f;
	TargetTag = "";
	ProjIndex = EmptyProj;
	ProjOffset = Vector2::Zero();

	Animations = new AnimStateMachine();


	Collision = new CollisionComponent(this);
	Collision->Dimensions.Position = Position;
	Collision->Dimensions.Width = 25.0f;
	Collision->Dimensions.Height = 25.0f;

	Physics = new PhysicsComponent(this);
	Physics->MaxVelocity = 1000.0f;
	Physics->Drag = 1.0f;

	STAnimationData AnimData;
	AnimData.MaxFrames = 10;
	AnimData.EndFrame = 9;
	AnimData.StartFrame = 0;
	AnimData.FPS = 24;

	SDL_Renderer* R = Game::GetGameInstance().GetGameStates()->GetCurrentState()->GetRenderer();

	Animations->AddAnimation(R, "Content/MainShip/Projectiles/Projectile - Big Space Gun.png", AnimData);

	AnimData.FPS = 24;
	AnimData.MaxFrames = 4;
	AnimData.EndFrame = 3;
	AnimData.StartFrame = 0;

	Animations->AddAnimation(R, "Content/MainShip/Projectiles/Nairan - Rocket.png", AnimData);
}

Projectile::~Projectile()
{
	delete Animations;
	Animations = nullptr;
}

void Projectile::Update()
{
	GameObject::Update();

	DeathTimer -= Game::GetGameInstance().GetFDeltaTime();

	Physics->AddForce(Direction, Acceleration);

	//check if we are overlapping a collider with the targettag
	if (Collision->IsOverlappingTag(TargetTag)) {
		//loop thru all targets
		for (CollisionComponent* Target : Collision->GetOverLappedByTag(TargetTag)) {
			//remove 1 life
			if (!Target->GetOwner()->ShouldDestroy()) {
				dynamic_cast<Character*>(Target->GetOwner())->RemoveLives(1);
				this->DestroyGameObject();
			}
		}
	}

	if (DeathTimer <= 0.0f) {
		this->DestroyGameObject();
	}
	
}

void Projectile::Draw(SDL_Renderer* Renderer)
{
	GameObject::Draw(Renderer);

	Animations->Draw(Renderer, 0, Position, Rotation, Scale, false);
}
