#include "VMEngine2D\Game.h"
#include "VMEngine2D/Vector2.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/Input.h"
#include "VMEngine2D/GameObjects/Character.h"
#include "VMEngine2D/GameObject.h"
#include "VMEngine2D/Animation.h"
using namespace std;

Game& Game::GetGameInstance()
{
	//Create a game instance only if there isn't one already
	//Local static variables can only be created once
	static Game* GameInstance = new Game();
	return *GameInstance;
}

void Game::DestroyGameInstance()
{
	//Store the game instance in a static variable
	static Game* GameInstance = &GetGameInstance();
	//remove the game instance from memory
	delete GameInstance;
}

Game::Game()
{
	cout << "Initialised Game Instance!" << endl;
	bIsGameOver = false;
	SdlWindow = nullptr;
	DeltaTime = 0.0;
	SdlRenderer = nullptr;
	PlayerInput = nullptr;

}

Game::~Game()
{
	cout << "Destroyed Game Instance..." << endl;
}

void Game::Start(const char* WTitle, bool bFullScreen, int WWidth, int WHeight)
{
	// Intialise SDL and end the game if it fails
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		//Error Handle
		cout << "SDL Failed to load: " << SDL_GetError() << endl;
	}

	// Default to Window Mode
	//Hold ctrl to see where SDL_WINDOW_SHOWN goes to and view other documentation.
	int FullScreenFlag = SDL_WINDOW_SHOWN;

	//If fullscreen is true then overwrite to full screen
	if (bFullScreen == true) {
		FullScreenFlag = SDL_WINDOW_FULLSCREEN;
	}

	//Create Window
	SdlWindow = SDL_CreateWindow(
		WTitle,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WWidth, WHeight,
		FullScreenFlag
	);

	//If the window wasn't created
	if (SdlWindow == nullptr) {
		//Error log
		cout << "SDL Window Creation failed: " << SDL_GetError() << endl;
		//Unintialise SDL
		SDL_Quit();
		return;
	}

	//set up the renderer
	SdlRenderer = SDL_CreateRenderer(SdlWindow, 0, -1);
	if (SdlRenderer == nullptr) {
		cout << "SDL Renderer creation failed: " << SDL_GetError() << endl;
		//remove the window
		SDL_DestroyWindow(SdlWindow);
		//uninitalise SDL
		SDL_Quit();
		return;
	}

	//create the input in the inisialisation stage
	PlayerInput = new Input();

	Run();
}

void Game::ProcessInput()
{
	//this must run before all other process inputs
	PlayerInput->ProcessInput();

//process the input  of each gameobject
	for(GameObject* SingleGameObject : AllGameObjects){
		SingleGameObject->ProcessInput(PlayerInput);
	}
}

void Game::Update()
{
	//static variables in methods will only initialise once
	// update with the previous fraames time passed
	static double LastTickTime = 0.0;
	// get the current time milliseconds that has passed since the game has started
	// GetTicks64 returns a Uint64 which means we need to convert it into the double
	double CurrentTickTime = static_cast<double>(SDL_GetTicks64());
	//get the difference between last tick time and current tick time
	double DeltaMil = CurrentTickTime - LastTickTime;
	//set delta time but convert it to seconds
	DeltaTime = DeltaMil / 1000.0;
	//set the last tick time as the current time for the next frame
	LastTickTime = CurrentTickTime;
}

void Game::Draw()
{
	//set background colour of app
	SDL_SetRenderDrawColor(SdlRenderer, 0, 50, 200, 255);
	//clear the previous frame
	SDL_RenderClear(SdlRenderer);

	//do anything that needs to be drawn to the screen here

	//cycle through all of the gameObjects in the ALLGameObjects array
	//each loop reassign the singleGameobject
	for (GameObject* SingleGameObject : AllGameObjects) {
		//each loop run the draw function for each gameobject
		SingleGameObject->Draw(SdlRenderer);
	}

	//Show the new frame
	SDL_RenderPresent(SdlRenderer);
}

void Game::Run()
{
	if (!bIsGameOver) {
		BeginPlay();
	}

	//check if the game over is false (something has thrown an error)
	//If not false run game loop
	while (!bIsGameOver) {
		ProcessInput();
		Update();
		Draw();
	}

	CloseGame();
}

void Game::CloseGame()
{
	//handle game asset deletion
	cout << "Deleting Game Assets..." << endl;

	//delete player input from memory
	delete PlayerInput;

	//Handle SDL unintialisation
	cout << "Cleaning up SDL" << endl;
	SDL_DestroyWindow(SdlWindow);
	SDL_Quit();
}

void Game::BeginPlay()
{
	cout << "Load Game Assets..." << endl;

	Character* MyCharacter = new Character(Vector2(100.0f, 100.0f));
	

	//Round Shield Animation
	STAnimationData AnimData1 = STAnimationData();
	AnimData1.FPS = 30;
	AnimData1.MaxFrames = 12;
	//the frames should be auumed as index by array values
	AnimData1.StartFrame = 0;
	AnimData1.EndFrame = 11;

	MyCharacter->AddAnimation(SdlRenderer,
		"Content/shipshields/Main Ship - Shields - Round Shield.png",
		AnimData1);

	//Invinciblity Shield Animation
	STAnimationData AnimData2 = STAnimationData();
	AnimData2.FPS = 30;
	AnimData2.MaxFrames = 10;
	AnimData2.StartFrame = 0;
	AnimData2.EndFrame = 9;

	MyCharacter->AddAnimation(SdlRenderer,
		"Content/shipshields/Main Ship - Shields - Invincibility Shield.png",
		AnimData2);

	//Front Shield Animation
	MyCharacter->AddAnimation(SdlRenderer,
		"Content/shipshields/Main Ship - Shields - Front Shield.png",
		AnimData2);

	//Cannon Animation
	STAnimationData AnimData4 = STAnimationData();
	AnimData4.FPS = 30;
	AnimData4.MaxFrames = 7;
	AnimData4.StartFrame = 0;
	AnimData4.EndFrame = 6;

	MyCharacter->AddAnimation(SdlRenderer,
		"Content/shipshields/Main Ship - Weapons - Auto Cannon.png",
		AnimData4);

	//Ship + Engine Animation
	STAnimationData StaticData = STAnimationData();
	StaticData.FPS = 0;
	StaticData.MaxFrames = 0;
	StaticData.StartFrame = 0;
	StaticData.EndFrame = 0;

	MyCharacter->AddAnimation(SdlRenderer,
		"Content/shipshields/Main Ship - Engines - Base Engine.png",
		StaticData);

	MyCharacter->AddAnimation(SdlRenderer,
		"Content/shipshields/Main Ship - Base - Full health.png",
		StaticData);

	STAnimationData AnimData5 = STAnimationData();
	AnimData5.FPS = 30;
	AnimData5.MaxFrames = 3;
	AnimData5.StartFrame = 0;
	AnimData5.EndFrame = 2;

	MyCharacter->AddAnimation(SdlRenderer,
		"Content/shipshields/Main Ship - Engines - Base Engine - Idle.png",
		AnimData5);

	AllGameObjects.push_back(MyCharacter);
}