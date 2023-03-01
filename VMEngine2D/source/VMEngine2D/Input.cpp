#include "VMEngine2D/Input.h"
#include "VMEngine2D/Game.h"
#include<iostream>

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
