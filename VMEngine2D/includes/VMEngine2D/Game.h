#pragma once
#include <iostream>
#include<vector>
#include "SDL2/SDL.h"

class GameObject;
class Input;
class CollisionComponent;

//at compile time the compiler will return the type definition into the proper one
typedef std::vector<CollisionComponent*>::iterator ColIterator;
typedef std::vector<GameObject*> ::iterator GOIterator;

class Game {
public:

	//Get the game singleton class
	//this will allow us to access global functions and variables -
	// - in the game class
	static Game& GetGameInstance();

	//Destroy the game
	static void DestroyGameInstance();

	//Initialise the Game before the loop runs
	void Start(const char* WTitle, bool bFullScreen, int WWidth, int WHeight);

	//For precise timing
	double GetDeltaTime() const { return DeltaTime; }

	//for average timing
	float GetFDeltaTime() const { return static_cast<float>(DeltaTime); }

	//sets bGameOver to true which closes the app
	void CloseApp() { bIsGameOver = true; }
	
	//add a collsision component to the component stack
	void AddCollisionTOGame(CollisionComponent* Collider);

	//remove collsion from the game
	void RemoveCollsionFromGame(CollisionComponent* Colldier);

	//return all the colldiers iin thee game
	std::vector<CollisionComponent*> GetGameCollider() const { return AllColliders; }
private:
	//Constructor
	Game();
	//Destructor
	~Game();

	//Handle the input of the user
	void ProcessInput();

	//Handle the game logic
	void Update();

	//Render the graphics to the screen
	void Draw();

	//Run the game loop
	void Run();

	//Clean up any memory we need to clean
	void CloseGame();

	//load game logic before the game update runs
	void BeginPlay();

	//remove things from memory at the end of the game loop
	void HandleGarbage();

private:
	//handle the game loop condition
	//on true end game
	bool bIsGameOver;

	//Store the app window
	SDL_Window* SdlWindow;

	//store the renderer to render graphics
	SDL_Renderer* SdlRenderer;

	//hold the time between each frame
	double DeltaTime;

	Input* PlayerInput;

	//gameobject stack
	std::vector<GameObject*> AllGameObjects;

	//collision stack
	std::vector<CollisionComponent*> AllColliders;


};