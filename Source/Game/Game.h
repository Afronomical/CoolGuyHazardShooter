#pragma once

#include <SDL.h>

//#include "Vector2.h"

class Game
{
public:
	Game(const char* _windowName/*, Vector2 _windowDimensions*/);
	
	bool Initialise();
	bool InitialiseSDL();
	bool InitialiseGame();

	void Run();

	void HandleInput();
	void Update(float deltaTime);
	void Draw();
	bool Clean();

	inline SDL_Renderer* GetRenderer() { return renderer; }
	inline void SetIsRunning(bool _isRunning) { isRunning = _isRunning; }

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool isRunning;
	const char* windowName;
	//Vector2 windowDimensions;
};

