#include "Game.h"

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


#include "../AssetLoading/AssetHandler.h"
#include "../Camera/Camera.h"
#include "../Collision/Collider.h"
#include "../Debugging/Debug.h"
#include "../Debugging/MemoryLeakDetector.h"
#include "../Enemies/BaseEnemy.h"
#include "../Player/Player.h"
#include "../FileHandling/FileHandler.h"
#include "../GameObject/GameObject.h"
#include "../Input/InputHandler.h"
#include "../Map/Map.h"
#include "../Time/Time.h"
#include "../UI/UIManager.h"

BaseEnemy* enemy;
Player* player1;
Player* player2;

std::shared_ptr<UIManager> uiManager;
std::shared_ptr<AssetHandler> assetHandler;


Game::Game(const std::string& _windowName, const Vector2& _windowDimensions) : window(nullptr), renderer(nullptr), isRunning(false), windowName(_windowName), 
																			   windowDimensions(_windowDimensions)
{
	// INFO: Initialise and Validate everything
	if (Initialise())
	{
		// INFO: Set the game to be running
		isRunning = true;
	}
}

Game::~Game()
{
	// INFO: Call Clean on destructor if we quit program unexpectedly
	Clean();
}

bool Game::Initialise()
{
	// INFO: Check to see if everything has been initialised correctly
	bool success = true;

	// INFO: Initialise and Validate SDL subsystems
	if (!InitialiseSDL()) 
	{
		Debug::LogError("Game::Initialise: SDL could not initialise!");
		return !success;
	}

	// INFO: Initialise and Validate the game
	if (!InitialiseGame())
	{
		Debug::LogError("Game::Initialise: Game could not initialise!");
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
		Debug::LogError("Game::InitialiseSDL: SDL could not initialise! SDL_Error: " + std::string(SDL_GetError()));
		return !success;
	}
	else
	{
		// INFO: Create the window
		SDL_WindowFlags windowFlags = SDL_WINDOW_RESIZABLE;

		window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
								  static_cast<int>(windowDimensions.X), static_cast<int>(windowDimensions.Y), windowFlags);

		// INFO: Window Validity Check
		if (window == nullptr)
		{
			Debug::LogError("Game::InitialiseSDL: Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
			return !success;
		}

		// INFO: Create the renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		// INFO: Renderer Validity Check
		if (renderer == nullptr)
		{
			Debug::LogError("Game::InitialiseSDL: Renderer could not be created! SDL_Error: " + std::string(SDL_GetError()));
			return !success;
		}

		// INFO: Initialise and Validate SDL Image
		int flags = IMG_INIT_JPG | IMG_INIT_PNG;

		if (IMG_Init(flags) != flags)
		{
			Debug::LogError("Game::InitialiseSDL: SDL Image could not initialise! SDL_Image Error: " + std::string(IMG_GetError()));
			return !success;
		}

		// INFO: Initialise and Validate SDL Mixer
		flags = MIX_INIT_MP3;

		if (Mix_Init(flags) != flags)
		{
			Debug::LogError("Game::InitialiseSDL: SDL Mixer could not initialise! SDL_Mixer Error: " + std::string(Mix_GetError()));
			return !success;
		}

		// INFO: Open and Validate the audio device
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			Debug::LogError("Game::InitialiseSDL: SDL Mixer could not open audio! SDL_Mixer Error: " + std::string(Mix_GetError()));
			return !success;
		}

		// INFO: Initialise and Validate SDL TTF
		if (TTF_Init() == -1)
		{
			Debug::LogError("Game::InitialiseSDL: SDL TTF could not initialise! SDL_TTF Error: " + std::string(TTF_GetError()));
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

	// INFO: Initialise the game and various systems here

	// INFO: Set the renderer for the Asset Handler and Debug
	AssetHandler::SetRenderer(renderer);
	Debug::SetRenderer(renderer);
	
	// INFO: Create the camera
	camera = std::make_shared<Camera>(static_cast<int>(windowDimensions.X), static_cast<int>(windowDimensions.Y));

	// INFO: Set the camera for the Asset Handler and GameObject Handler
	AssetHandler::SetCamera(camera);
	GameObject::Handler::SetCamera(camera);

	// INFO: create ui manager 
	uiManager = std::make_shared<UIManager>(camera, assetHandler);

	// INFO: Initialise the Input System
	InputHandler::Initialise();

	// INFO: Set up the on quit function for the Input System
	InputHandler::SetOnQuit([&]() { isRunning = false; });

	// INFO: Load the map that will be used as the current map
	if (!FileHandler::LoadMap("TestMap", "Assets/Maps/TestMap.tmx"))
	{
		Debug::LogError("Game::InitialiseGame: Failed to load map!");
		return !success;
	}

	// INFO: Set the current map
	currentMap = FileHandler::InitialiseMap("TestMap");
	
	enemy = new BaseEnemy();
	player1 = new Player(true);
	player2 = new Player(false);

	return success;
}

void Game::Run()
{
	// INFO: Call the Start function for all game objects
	GameObject::Handler::Start();

	// INFO: Game Loop
	while (isRunning)
	{
		Time::Tick();

		HandleInput();
		Update(Time::DeltaTime());

		// INFO: Check collision between all colliders
		Collider::Handler::CheckCollisions();

		Draw();

		// INFO: Process deletion of game objects that have been queued for deletion
		GameObject::Handler::ProcessDeletionQueue();
	}
}

void Game::HandleInput()
{
	InputHandler::HandleInputs();
}

void Game::Update(float deltaTime)
{
	// INFO: Call the Update function for all game objects
	GameObject::Handler::Update(deltaTime);

	// INFO: Call the LateUpdate function for all game objects
	GameObject::Handler::LateUpdate(deltaTime);
}

void Game::Draw()
{
	// INFO: Clear the renderer
	SDL_RenderClear(renderer);

	// INFO: Draw the current map if it exists
	if (!currentMap.expired())
		currentMap.lock()->Draw();

	// INFO: Call the Draw function for all game objects
	GameObject::Handler::Draw();

	//testing UI text 
	SDL_Rect textRect = { 100, 50, 200, 50 };
	uiManager->RenderText("Text Test", textRect, renderer);
	
	
	// INFO: Present the renderer
	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	// INFO: Clean up game objects
	GameObject::Handler::Clean();

	// INFO: Clean up the Asset Handler
	AssetHandler::Clean();

	// INFO: Clean up the Input Handler
	InputHandler::Clean();

	// INFO: Remove the renderer from game
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	// INFO: Remove the window from game
	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	// INFO: Clean up SDL subsystems
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}
