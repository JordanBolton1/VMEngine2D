#include "VMEngine2D/Game.h"

int main(int argc, char** argv) {
	//This will run until the game loop fails
	Game::GetGameInstance().Start("VMEngine2D | Powered by SDL2", false, 980, 540);

	//This will end the app
	Game::DestroyGameInstance();

	return 0;
}