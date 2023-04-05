#include "VMEngine2D/GameStates/PlayState.h"
#include "VMEngine2D/GameObjects/Characters/Enemy.h"
#include "VMEngine2D/GameObjects/Characters/Player.h"
#include "VMEngine2D/Text.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/GameStates/GameOver.h"

PlayState::PlayState(SDL_Window* Window, SDL_Renderer* Renderer) : GameState(Window, Renderer)
{
	ScoreText = nullptr;
	SpawnTimer = 0.0;
	SpawnTime = 5.0;
}

void PlayState::BeginState()
{
	GameState::BeginState();

	Player* MyCharacter = new Player(Vector2(100.0f, 100.0f), StateRenderer);
	// ad the characetr into the gaameobject stack
	ActivateGameObject(MyCharacter);

	//create aan empty text object
	ScoreText = new Text(StateRenderer);
	
	//ajust text settings
	STTextInfo TestInfo;
	TestInfo.TextStr = "Hello World";
	TestInfo.Size = 40;
	TestInfo.Position = Vector2(50.0f, 50.0f);

	//initialise the text 
	ScoreText->InitText("Content/Fonts/dogica.ttf", TestInfo);

	//add text to the game
	ActivateTextObject(ScoreText);
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
		ActivateGameObject(NewEnemy);

		//reset timer to 0 and start again
		SpawnTimer = 0.0;
		SpawnTime *= 0.99;

		//wont let spawn timer spawn faster tthan 1 second
		if (SpawnTime < 1.0) {
			SpawnTime = 1.0;
		}
	}
	ScoreText->SetText("Score: " + to_string(Game::GetGameInstance().GameScore));

	//after score is obtained switch to game over
	if (Game::GetGameInstance().GameScore > 200) {
		PlayState* NewState = new PlayState(StateWindow, StateRenderer);

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
