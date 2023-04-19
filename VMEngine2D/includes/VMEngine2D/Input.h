#pragma once
#include "SDL2/SDL.h"
class Input {
public:
	Input();
	~Input();

	//run all the input detection logic
	void ProcessInput();

	//return whether or no the key is down
	bool IsKeyDown(SDL_Scancode key);

private:

	//hold all the sttes of each key on the keboard (pressed or released)
	const Uint8* KeyboardState;

	//run the listeners foe the windows menu events
	void HandleWMEvents(SDL_Event* Event);

};