#include "VMEngine2D\Game.h"
#include "VMEngine2D/Vector2.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/Input.h"
#include "VMEngine2D/GameObjects/Characters/Player.h"
#include "VMEngine2D/GameObjects/Characters/Enemy.h"
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

void Game::AddCollisionTOGame(CollisionComponent* Collider)
{
	//Add a collsion into the allcollider stack
	AllColliders.push_back(Collider);

	std::cout << "added collision" << std::endl;
}

void Game::RemoveCollsionFromGame(CollisionComponent* Collider)
{
	//the find function finds an object or data using the object in a vector stack
	//@Param 1 - look from the start of the array
	//@Param 2 - to trhe end of the array
	//@Param 3 - the object that we aare searching for
	ColIterator ColToRemove = std::find(AllColliders.begin(),AllColliders.end(), Collider);

	//the  find function will set the iterator to allcolliders .end() if it didnt find anything
	if (ColToRemove == AllColliders.end()) {
		//didnt find the collision
		return;//return will kill the rest of the function if its run
	}

	//remove the collidier if the fiind funtion found the collider
	AllColliders.erase(ColToRemove);

	std::cout << "removed collision" << std::endl;
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

	//run last gameobject logic
	for (GameObject* SingleGameObject : AllGameObjects) {
		SingleGameObject->Update();
	}

	//set a static timer to count up based on deltatime
	//static variables dont reinitialise
	static double SpawnTimer = 0.0;
	SpawnTimer += DeltaTime;

	if (SpawnTimer > 5.0) {
		//set up
		int WinWidth, WinHeight = 0;

		SDL_GetWindowSize(SdlWindow, &WinWidth, &WinHeight);

		WinWidth += 1;
		WinWidth -= 128;

		int SpawnEnemyX = rand() %WinWidth;

		Enemy* NewEnemy = new Enemy(Vector2(SpawnEnemyX,-128.0f), SdlRenderer);

		AllGameObjects.push_back(NewEnemy);

		SpawnTimer = 0.0;
	}
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
		HandleGarbage();
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

	Player* MyCharacter = new Player(Vector2(100.0f, 100.0f), SdlRenderer);
	Enemy* Bomber = new Enemy(Vector2(300.0f, 100.0f), SdlRenderer);
	// ad the characetr into the gaameobject stack
	AllGameObjects.push_back(Bomber);
	AllGameObjects.push_back(MyCharacter);
	
}

void Game::HandleGarbage()
{
	//loop thru all of the gameoobject and assign the iterator each loop
	for (GOIterator Object = AllGameObjects.begin(); Object != AllGameObjects.end();) {
		//if the object is not marked for delte then increment and skip to the next one
		if (!(*Object)->ShouldDestroy()) {
			Object++;
			continue;
		}

		//delete the gamobject
		delete* Object;

		//remove the object from the array and resize the array
		Object = AllGameObjects.erase(Object);

		std::cout << "delte gameObject" << std::endl;
	}
}
