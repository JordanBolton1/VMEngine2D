#pragma once
#include <iostream>
#include<vector>
#include "SDL2/SDL.h"

class GameObject;
class Input;
class CollisionComponent;
class GameStateMachine;
class WindowMenu;


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
	


	//return all the colldiers iin thee game
	std::vector<CollisionComponent*> GetGameCollider() const;

	//return the gamesstate machine
	GameStateMachine* GetGameStates() { return GameStates; }

	//get the top level windows system menu
	WindowMenu* GetTopMenu() const { return TopMenu; }

	//this will restart game
	void RestartGame();

public:
	//store current players score
	unsigned int GameScore;


private:
	//Constructor
	Game();
	//Destructor
	~Game();

	//add things into the game
	void Instantiate();

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

	//store the current gamestate
	GameStateMachine* GameStates;

	//
	WindowMenu* TopMenu;

};