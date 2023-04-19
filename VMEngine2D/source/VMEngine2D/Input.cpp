#include "VMEngine2D/Input.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/WindowMenu.h"
#include "SDL2/SDL_syswm.h"
#include<iostream>
#include"../resource.h"


Input::Input()
{
	//assigning all th states of the keyss to the keyboard state
	//NULL means get all the keys
	KeyboardState = SDL_GetKeyboardState(NULL);
}

Input::~Input()
{
	
}

void Input::ProcessInput()
{
	//This stores the inputs as an event
	SDL_Event PollEvent;

	//This will listen to the event and end the loop after all inputs are detected.
	while (SDL_PollEvent(&PollEvent)) {
		//detect the type of event that was input
		switch (PollEvent.type) {
		case SDL_KEYDOWN:
			//set the keyboard state
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_KEYUP:
			//set the keyboard state
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_QUIT:
			//go into the game instance and run the Close
			Game::GetGameInstance().CloseApp();
			break;
		case SDL_SYSWMEVENT:
			HandleWMEvents(&PollEvent);
			break;
		default:
			break;
		}
	}
}

bool Input::IsKeyDown(SDL_Scancode Key)
{
	//if the keystate doesnt exist then dont run ffunction
	if (KeyboardState == nullptr) {
		return false;
	}

// return the value of the key = true or false
	return KeyboardState[Key];
}

void Input::HandleWMEvents(SDL_Event* Event)
{
	//listen out for system windowmenu button presses
	switch (Event->syswm.msg->msg.win.wParam) {
	case ID_FILE_RESTARTGAME :
		Game::GetGameInstance().RestartGame();
		break;
	case ID_FILE_EXITAPP :
		Game::GetGameInstance().CloseApp();
		break;
	case ID_GAME_CONTROLS:
		Game::GetGameInstance().GetTopMenu()->ActivatePopup(
			"Game Controls",	//title
			"WASD - Move Player \n Space - Shoot \n Q - Activate Shield"	//message
		);
		break;
	case ID_HELP_ABOUTVMENIGINE2D:
		Game::GetGameInstance().GetTopMenu()->ActivatePopup(
			"About",//title
			"MMM yes"//message
		);
		break;
	default:
		break;
	}
}
