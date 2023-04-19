#include "VMEngine2D/WindowMenu.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"
#include "../resource.h"//dbl dots look outside icludes
#include<Windows.h>
#include<iostream>
#include "VMEngine2D/Game.h"

WindowMenu::WindowMenu(SDL_Window* Window)
{
	//initialise the window menu values
	this->Window = Window;
	WindowInfo = new SDL_SysWMinfo();

	//update window info
	SDL_VERSION(&WindowInfo->version);
	//after we have the version sdl will aloow us to assign the rest of the info usinf an sdl function
	SDL_GetWindowWMInfo(Window, WindowInfo);
}

WindowMenu::~WindowMenu()
{
	//set window tyo nulptr but dont delte ass the game.cpp handles that
	Window = nullptr;

	//delete the window info object
	delete WindowInfo;
	WindowInfo = nullptr;
}

void WindowMenu::CreateMenuFromResource()
{
	//we need to convert our sdl window info into a system window
	HWND SysWindow = WindowInfo->info.win.window;
	//we need to get the resource menu that we created in visual studio
	//get module handle(0) get the current instance of the windo that we are activley in
	HINSTANCE WindowInstance = GetModuleHandle(0);	
	//MAKEINTRESOURCE will convert the idr_menu1 into a LPCWSTR which has the index for the menu
	LPCWSTR VSMenu = MAKEINTRESOURCE(IDR_MENU1);
	//load the menu selected to the active window
	HMENU SysMenu = LoadMenu(WindowInstance, VSMenu);

	//this adds the menu to the window
	//if it fails then error log and stop the function
	if (!SetMenu(SysWindow, SysMenu)) {
		std::cout << "Menu coudnt be set" << std::endl;
	}

	//if the menu was successfully added then activate the listener for sdl events
	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
}

void WindowMenu::RestartGame()
{
	//reun the restart game function
	Game::GetGameInstance().RestartGame();
}

void WindowMenu::ExitApp()
{
	//run the close app function
	Game::GetGameInstance().CloseApp();
}

void WindowMenu::ActivatePopup(const char* Title, const char* Message)
{
	//create a message box that will show on screen with title and message
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, Title, Message, Window);
}
