#include "Game.h"

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "TimeClass.h"

#include "../GameObject/PlayerTest.h"

//#include "../Debug/Debug.h"
//#incldue "../Input/InputHandler.h"
//#include "../Time/Time.h"

Game::Game(const char* _windowName, const Vector2& _windowDimensions) : window(nullptr), renderer(nullptr), isRunning(false),
																		windowName(_windowName), windowDimensions(_windowDimensions)
{
	// INFO: Initialise and Validate everything
	if (Initialise())
	{
		Run();
	}
	else
	{
		//Debug::LogError("Game could not initialise!");
	}
}

bool Game::Initialise()
{
	// INFO: Check to see if everything has been initialised correctly
	bool success = true;

	PlayerTest playerTest;

	// INFO: Initialise and Validate SDL subsystems
	if (!InitialiseSDL()) 
	{
		//Debug::LogError("SDL could not initialise!");
		return !success;
	}

	// INFO: Initialise and Validate the game
	if (!InitialiseGame())
	{
		//Debug::LogError("Game could not initialise!");
		return !success;
	}

	
	return success;
}

bool Game::InitialiseSDL()
{
	// INFO: Check to see if everything has been initialised correctly
	bool success = true;

	// INFO: Initialise and Validate SDL
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_SENSOR) < 0)
	{
		//Debug::LogError("SDL could not initialise! SDL_Error: %s", SDL_GetError());
		return !success;
	}
	else
	{
		// INFO: Create the window
		window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, static_cast<int>(windowDimensions.X), static_cast<int>(windowDimensions.Y), NULL);

		// INFO: Window Validity Check
		if (window == nullptr)
		{
			//Debug::LogError("Window could not be created! SDL_Error: %s", SDL_GetError());
			return !success;
		}

		// INFO: Create the renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		// INFO: Renderer Validity Check
		if (renderer == nullptr)
		{
			//Debug::LogError("Renderer could not be created! SDL_Error: %s", SDL_GetError());
			return !success;
		}

		// INFO: Initialise and Validate SDL Image
		int flags = IMG_INIT_JPG | IMG_INIT_PNG;

		if (IMG_Init(flags) != flags)
		{
			//Debug::LogError("SDL Image could not initialise! SDL_Image Error: %s", IMG_GetError());
			return !success;
		}

		// INFO: Initialise and Validate SDL Mixer
		flags = MIX_INIT_MP3;

		if (Mix_Init(flags) != flags)
		{
			//Debug::LogError("SDL Mixer could not initialise! SDL_Mixer Error: %s", Mix_GetError());
			return !success;
		}

		// INFO: Open and Validate the audio device
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			//Debug::LogError("SDL Mixer could not open audio! SDL_Mixer Error: %s", Mix_GetError());
			return !success;
		}

		// INFO: Initialise and Validate SDL TTF
		if (TTF_Init() == -1)
		{
			//Debug::LogError("SDL TTF could not initialise! SDL_TTF Error: %s", TTF_GetError());
			return !success;
		}

		// INFO: Set the initial window colour
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
	}

	return success;
}

bool Game::InitialiseGame()
{
	// INFO: Check to see if everything has been initialised correctly
	bool success = true;

	// NOTE: Initialise the game and various systems here

	// INFO: Set the game to be running
	isRunning = false;

	return success;
}

void Game::Run()
{
	// NOTE: Game Loop
	while (isRunning)
	{
		HandleInput();
		//Update(Time::DeltaTime());
		Draw();
		//Time::Tick();
	}

	// NOTE: Clean up the game
	Clean();
}

void Game::HandleInput()
{
}

void Game::Update(float deltaTime)
{
}

void Game::Draw()
{
}

void Game::Clean()
{
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}
}
