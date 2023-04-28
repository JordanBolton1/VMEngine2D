#include "VMEngine2D\Game.h"
#include "VMEngine2D/Vector2.h"
#include "VMEngine2D/Input.h"
#include "VMEngine2D/GameObject.h"
#include "VMEngine2D/GameState.h"
#include "VMEngine2D/GameStates/PlayState.h"
#include "VMEngine2D/WindowMenu.h"
#include "VMEngine2D/GameStates/SplashState.h"

#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

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

std::vector<CollisionComponent*> Game::GetGameCollider() const
{
	return GameStates->GetCurrentState()->GetGameStateCollisions();
}

Game::Game()
{
	cout << "Initialised Game Instance!" << endl;
	bIsGameOver = false;
	SdlWindow = nullptr;
	DeltaTime = 0.0;
	SdlRenderer = nullptr;
	PlayerInput = nullptr;
	GameStates = nullptr;
	GameScore = 0;
	TopMenu = nullptr;
}

void Game::RestartGame()
{
	//rewset game score
	GameScore = 0;

	//create a newe starting state
	PlayState* NewState = new PlayState(SdlWindow, SdlRenderer);
	GetGameStates()->SwitchState(NewState);
}

Game::~Game()
{
	cout << "Destroyed Game Instance..." << endl;
}

void Game::Instantiate() {
	//run the game staes in instantiate
	GetGameStates()->GetCurrentState()->Instantiate();
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
	
		CloseGame();
		return;
	}

	//set up the renderer
	SdlRenderer = SDL_CreateRenderer(SdlWindow, 0, -1);
	if (SdlRenderer == nullptr) {
		cout << "SDL Renderer creation failed: " << SDL_GetError() << endl;

		CloseGame();
		return;
	}
	
	//initialise ttf and if equals -1 it fails 0 means it succeeds
	if (TTF_Init() < 0) {
		cout << "sld ttf failed" << TTF_GetError() << endl;

		CloseGame();
		return;
	}

	//initialise mixer/ audio system
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096)< 0) {
		cout << "sdl Mixer failed" << SDL_GetError() << endl;

		CloseGame();
		return;
	}

	//create a menu for the window
	TopMenu = new WindowMenu(SdlWindow);
	//add the menu to the window
	TopMenu->CreateMenuFromResource();

	//create the input in the inisialisation stage
	PlayerInput = new Input();

	//will randomise seed using time so we have different random seed everytime we open the game
	srand(time(NULL));

	Run();
}

void Game::ProcessInput()
{
	//this must run before all other process inputs
	PlayerInput->ProcessInput();

	//run the input of the current game state
	GameStates->GetCurrentState()->ProcessInput(PlayerInput);
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

	//run the update of the curreent state and pass in flaot deltatime
	GameStates->GetCurrentState()->Update(GetFDeltaTime());

}

void Game::Draw()
{
	//set background colour of app
	SDL_SetRenderDrawColor(SdlRenderer, 0, 0, 70, 100);
	//clear the previous frame
	SDL_RenderClear(SdlRenderer);

	//do anything that needs to be drawn to the screen here
	//run the gamestate draw
	GameStates->GetCurrentState()->Draw(SdlRenderer);
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
		Instantiate();

		ProcessInput();

		Update();

		Draw();

		HandleGarbage();
	}

	CloseGame();
}

void Game::CloseGame()
{
	if (GameStates != nullptr) {
		//handle game asset deletion
		cout << "Deleting Game Assets..." << endl;
		delete GameStates;
	}

	if (PlayerInput != nullptr) {
		//delete player input from memory
		delete PlayerInput;
	}

	//Handle SDL unintialisation
	cout << "Cleaning up SDL" << endl;

	if (SdlWindow != nullptr) {
		SDL_DestroyWindow(SdlWindow);
	}
	if (SdlRenderer != nullptr) {
		SDL_DestroyRenderer(SdlRenderer);
	}

	//delete the audio system from memory
	Mix_CloseAudio();

	SDL_Quit();
}

void Game::BeginPlay()
{
	cout << "Load Game Assets..." << endl;
	SplashState* StartingState = new SplashState(SdlWindow, SdlRenderer);
	//create a game state machine and
	GameStates = new GameStateMachine(StartingState);


}

void Game::HandleGarbage()
{
	GameStates->GetCurrentState()->HandleGarbage();
}
