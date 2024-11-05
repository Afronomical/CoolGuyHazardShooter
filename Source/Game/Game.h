#pragma once

#include <SDL.h>

#include <string>

#include "../Vector2/Vector2.h"

class Game
{
public:
	Game(const std::string& _windowName, const Vector2& _windowDimensions);
	
	/// @brief Utility function that encapsulates SDL and game initialisation
	/// @retval TRUE : If everything was initialised correctly
	/// @retval FALSE : If something went wrong during initialisation
	bool Initialise();

	/// @brief Utility function that encapsulates SDL initialisation
	/// @retval TRUE : If SDL was initialised correctly
	/// @retval FALSE : If SDL was not initialised correctly
	bool InitialiseSDL();

	/// @brief Utility function that encapsulates game initialisation
	/// @retval TRUE : If the game was initialised correctly
	/// @retval FALSE : If the game was not initialised correctly
	bool InitialiseGame();

	/// @brief Utility function that encapsulates the game loop
	void Run();

	/// @brief Calls the HandleInputs function of the InputHandler
	void HandleInput();
	
	/// @brief Updates all game objects
	/// @param deltaTime : The time between frames
	void Update(float deltaTime);

	/// @brief Draws all game objects
	void Draw();

	/// @brief Utility function that encapsulates game cleanup
	void Clean();

	inline void SetIsRunning(bool _isRunning) { isRunning = _isRunning; }

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool isRunning;
	std::string windowName;
	Vector2 windowDimensions;
};

