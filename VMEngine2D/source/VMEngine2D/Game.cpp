#include "VMEngine2D\Game.h"
#include "VMEngine2D/Vector2.h"
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

	//Intialise Animation Objects
	Animation1 = nullptr;
	Animation2 = nullptr;
	Animation3 = nullptr;
	Animation4 = nullptr;
	Animation5 = nullptr;

	//Overlay Image Objects
	EngineImage = nullptr;
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

	Run();
}

void Game::ProcessInput()
{
	//This stores the inputs as an event
	SDL_Event PollEvent;

	//This will listen to the event and end the loop after all inputs are detected.
	while (SDL_PollEvent(&PollEvent)) {
		//detect the type of event that was input
		switch (PollEvent.type) {
		case SDL_QUIT:
			bIsGameOver = true;
			break;
		default:
			break;
		}
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
	Animation1->Draw(SdlRenderer, Vector2(100.0f, 100.0f), 2.0f, false);
	Animation2->Draw(SdlRenderer, Vector2(300.0f, 100.0f), 1.0f, false);
	Animation3->Draw(SdlRenderer, Vector2(500.0f, 300.f), 3.0f, false);
	Animation4->Draw(SdlRenderer, Vector2(100.0f, 300.0f), 5.0f, true);
	Animation5->Draw(SdlRenderer, Vector2(750.0f, 120.0f), 5.0f, false);
	EngineImage->Draw(SdlRenderer, Vector2(750.0f, 110.0f), 5.0f, false);
	ShipImage->Draw(SdlRenderer, Vector2(750.0f, 100.0f), 5.0f, false);

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
	delete Animation1;

	//Handle SDL unintialisation
	cout << "Cleaning up SDL" << endl;
	SDL_DestroyWindow(SdlWindow);
	SDL_Quit();
}

void Game::BeginPlay()
{
	cout << "Load Game Assets..." << endl;

	//Round Shield Animation
	STAnimationData AnimData1 = STAnimationData();
	AnimData1.FPS = 30;
	AnimData1.MaxFrames = 12;
	//the frames should be auumed as index by array values
	AnimData1.StartFrame = 0;
	AnimData1.EndFrame = 11;

	Animation1 = new Animation(SdlRenderer,
		"Content/shipshields/Main Ship - Shields - Round Shield.png",
		AnimData1);

	//Invinciblity Shield Animation
	STAnimationData AnimData2 = STAnimationData();
	AnimData2.FPS = 30;
	AnimData2.MaxFrames = 10;
	AnimData2.StartFrame = 0;
	AnimData2.EndFrame = 9;

	Animation2 = new Animation(SdlRenderer,
		"Content/shipshields/Main Ship - Shields - Invincibility Shield.png",
		AnimData2);

	//Front Shield Animation
	Animation3 = new Animation(SdlRenderer,
		"Content/shipshields/Main Ship - Shields - Front Shield.png",
		AnimData2);

	//Cannon Animation
	STAnimationData AnimData4 = STAnimationData();
	AnimData4.FPS = 30;
	AnimData4.MaxFrames = 7;
	AnimData4.StartFrame = 0;
	AnimData4.EndFrame = 6;

	Animation4 = new Animation(SdlRenderer,
		"Content/shipshields/Main Ship - Weapons - Auto Cannon.png",
		AnimData4);

	//Ship + Engine Animation
	STAnimationData StaticData = STAnimationData();
	StaticData.FPS = 0;
	StaticData.MaxFrames = 0;
	StaticData.StartFrame = 0;
	StaticData.EndFrame = 0;

	EngineImage = new Animation(SdlRenderer,
		"Content/shipshields/Main Ship - Engines - Base Engine.png",
		StaticData);

	ShipImage = new Animation(SdlRenderer,
		"Content/shipshields/Main Ship - Base - Full health.png",
		StaticData);

	STAnimationData AnimData5 = STAnimationData();
	AnimData5.FPS = 30;
	AnimData5.MaxFrames = 3;
	AnimData5.StartFrame = 0;
	AnimData5.EndFrame = 2;

	Animation5 = new Animation(SdlRenderer,
		"Content/shipshields/Main Ship - Engines - Base Engine - Idle.png",
		AnimData5);
}