#pragma once

#include <iostream>
#include <string>

#include "../Collision/BoxCollider.h"
#include "../Collision/CircleCollider.h"
#include "../Color/Color.h"
#include "../Vector2/Vector2.h"

struct SDL_Renderer;

class Debug
{
public:
	static void DrawColliderOutline(std::shared_ptr<BoxCollider> boxCollider, const Color& color = Color::Green);
	static void DrawColliderOutline(std::shared_ptr<CircleCollider> circleCollider, const Color& color = Color::Green);
	static void DrawLine(const Vector2& start, const Vector2& end, const Color& color = Color::Red);

	/// @brief Allows for logging of messages to the console
	static inline void Log(std::string message) { std::cout << message << std::endl; }

	/// @brief Allows for logging of warning messages (yellow) to the console
	static void LogWarning(std::string message);

	/// @brief Allows for logging of error messages (red) to the console
	static void LogError(std::string message);

	static inline void SetRenderer(SDL_Renderer* _renderer) { renderer = _renderer; }

private:
	static SDL_Renderer* renderer;
};

