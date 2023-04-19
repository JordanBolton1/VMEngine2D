#pragma once

struct SDL_Window;
struct SDL_SysWMinfo;

class WindowMenu {

public: 
	WindowMenu(SDL_Window* Window);
	~WindowMenu();

	//create the menu and add it too the window usng a visual studio recpource
	void CreateMenuFromResource();

	//restrt the game without cosing the app
	void RestartGame();

	//close the app completly
	void ExitApp();
	
	//loasd dialog box that will provide th message
	void ActivatePopup(const char* Title, const char* Message);

private:
	//sdl window for the menu
	SDL_Window* Window;
	//system version of the window
	SDL_SysWMinfo* WindowInfo;
};