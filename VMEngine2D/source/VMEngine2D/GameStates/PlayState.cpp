#include "VMEngine2D/GameStates/PlayState.h"
#include "VMEngine2D/GameObjects/Characters/Enemy.h"
#include "VMEngine2D/GameObjects/Characters/Player.h"
#include "VMEngine2D/Text.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/GameStates/GameOver.h"
#include "VMEngine2D/GameObjects/Characters/Collectable.h"

PlayState::PlayState(SDL_Window* Window, SDL_Renderer* Renderer) : GameState(Window, Renderer)
{
	ScoreText = nullptr;
	SpawnTimer = 0.0;
	SpawnTime = 5.0;
	PlayerCharacter = nullptr;
	LivesText = nullptr;
	ColSpawnTime = 20.0;
	ColSpawnTimer = 0.0;

}

void PlayState::BeginState()
{
	GameState::BeginState();

	PlayerCharacter = new Player(Vector2(100.0f, 100.0f), StateRenderer);
	// ad the characetr into the gaameobject stack
	SpawnGameObject(PlayerCharacter);

	//create aan empty text object
	ScoreText = new Text(StateRenderer);
	
	//ajust text settings
	STTextInfo ScoreInfo;
	ScoreInfo.TextStr = "Hello World";
	ScoreInfo.Size = 20;
	ScoreInfo.Position = Vector2(20.0f, 20.0f);

	//initialise the text 
	ScoreText->InitText("Content/Fonts/dogica.ttf", ScoreInfo);

	//add text to the game
	ActivateTextObject(ScoreText);

	//creat new text elelment
	LivesText = new Text(StateRenderer);

	//initialise a width and height int
	int w, h = 0;

	//get the window size and set the width and height
	SDL_GetWindowSize(StateWindow, &w, &h);

	//adjust the starting setting
	STTextInfo LivesInfo;
	LivesInfo.TextStr = "Lives: ##";
	LivesInfo.Size = 20;
	//set the y pos of the text using the height of the windowe
	LivesInfo.Position = Vector2(25.0f, static_cast<float>(h));

	//create text using the setting and font
	LivesText->InitText("Content/Fonts/dogica.ttf", LivesInfo);

	//create a new position for the text accounting for the height of the text then offsetting
	Vector2 NewTextPos;
	NewTextPos.x = LivesText->GetTextInfo().Position.x;
	NewTextPos.y = LivesText->GetTextInfo().Position.y- LivesText->GetTextInfo().Dimensions.y - 20.0f;

	//update position
	LivesText->SetTextPostion(NewTextPos);

	//addlives teexct to the gamestate
	ActivateTextObject(LivesText);

}

void PlayState::ProcessInput(Input* PlayerInput)
{
	GameState::ProcessInput(PlayerInput);
}

void PlayState::Update(float DeltaTime)
{
	GameState::Update(DeltaTime);
	//set a static timer to count up based on deltatime
	//static variables dont reinitialise

	SpawnTimer += DeltaTime;
	ColSpawnTimer += DeltaTime;

	if (SpawnTimer > SpawnTime) {
		//set up variable3s to  recieve the app window width and height
		int WinWidth, WinHeight = 0;
		//use sdl function to set the dimnsions
		SDL_GetWindowSize(StateWindow, &WinWidth, &WinHeight);

		//increase window wdth by 1
		WinWidth += 1;
		WinWidth -= 128;

		//get a random number between 0 and window width
		//rand() gets random number between 0 and numbr after %
		int SpawnEnemyX = rand() % WinWidth;

		//spawn an enemy based on a randomsreen x location
		Enemy* NewEnemy = new Enemy(Vector2(SpawnEnemyX, -128.0f), StateRenderer);

		//add the enemy to the game object stack
		SpawnGameObject(NewEnemy);

		//reset timer to 0 and start again 
		SpawnTimer = 0.0;
		SpawnTime *= 0.99;

		//wont let spawn timer spawn faster tthan 1 second
		if (SpawnTime < 1.0) {
			SpawnTime = 1.0;
		}
	}
	if (ColSpawnTimer > ColSpawnTime) {
		//set up variable3s to  recieve the app window width and height
		int WinWidth, WinHeight = 0;
		//use sdl function to set the dimnsions
		SDL_GetWindowSize(StateWindow, &WinWidth, &WinHeight);

		//increase window wdth by 1
		WinWidth += 1;
		WinWidth -= 128;

		//get a random number between 0 and window width
		//rand() gets random number between 0 and numbr after %
		int SpawnColX = rand() % WinWidth;

		//spawn an enemy based on a randomsreen x location
		Collectables* NewCol = new Collectables(Vector2(SpawnColX, 50.0f), StateRenderer);

		//add the enemy to the game object stack
		SpawnGameObject(NewCol);

		//reset timer to 0 and start again 
		ColSpawnTimer = 0.0;
		ColSpawnTime *= 0.99;

		//wont let spawn timer spawn faster tthan 1 second
		if (ColSpawnTime < 2.0) {
			ColSpawnTime = 2.0;
		}
	}
	ScoreText->SetText("Score: " + to_string(Game::GetGameInstance().GameScore));

	//update lives text
	LivesText->SetText("Lives: " + to_string(PlayerCharacter->GetLives() - 1));

	//after score is obtained o player is defeated switch to game over
	if (Game::GetGameInstance().GameScore >= 50 || PlayerCharacter->GetLives() == 0) {
		GameOverState* NewState = new GameOverState(StateWindow, StateRenderer);

		Game::GetGameInstance().GetGameStates()->SwitchState(NewState);
	}
}

void PlayState::Draw(SDL_Renderer* Renderer)
{
	GameState::Draw(Renderer);
}

void PlayState::EndState()
{
	GameState::EndState();

	ScoreText = nullptr;
}
