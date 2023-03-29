#pragma once
#include <iostream>
#include<vector>


struct SDL_Renderer;
struct SDL_Window;
class Input;
class GameObject;
class CollisionComponent;

using namespace std;
//at compile time the compiler will return the type definition into the proper one
typedef vector<GameObject*> ::iterator GOIterator;
typedef vector<CollisionComponent*>::iterator ColIterator;

class GameState {
public:

	GameState(SDL_Window* Window,SDL_Renderer* Renderer);
	~GameState();

	
	void ProcessInput(Input* PlayerInput);

	void Update(float DeltaTime);

	void Draw(SDL_Renderer* Renderer);

	void HandleGarbage();

	//add a collsision componentt into the game state collisions stack
	void AddCollisionToGameState(CollisionComponent* Collision);

	void RemoveCollisionFromGameState(CollisionComponent* Collision);

	vector<CollisionComponent*> GetGameStateCollisions() { return StateCollision; }

	//run when state update for the first time
	void BeginState();

	//run when state u[pdate finishes
	void EndState();

	
protected:
	//window assigned to this state
	SDL_Window* StateWindow;
	//the renderer assigned to this tsate
	SDL_Renderer* StateRenderer;
private:

	//store all gameobject specifi to the state
	vector<GameObject*>StateGameObject;

	//all of thee collsision components specfic to the state
	vector<CollisionComponent*> StateCollision;

	//determine when the begin playe is activated
	bool bHasActivated;
};

class GameStateMachine {
public:
	GameStateMachine(GameState* StartingState);
	~GameStateMachine();

	//swith the current stste with the neew state
	void SwitchState(GameState* NewState);

	//add a state into the state stack 
	//will not destroy the current state
	void PushState(GameState* NewState);

	//removes the last state that was added from the stack
	void PopState();

	//return the last added state
	GameState* GetCurrentState() const { return GameStateStack.back(); }

private:
	vector<GameState*> GameStateStack;


};