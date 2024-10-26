#pragma once

#include <iostream>
#include <string>

//#include "../Collision/BoxCollider.h"
//#include "../Collision/CircleCollider.h"
#include "../Color/Color.h"
#include "../Vector2/Vector2.h"

struct SDL_Renderer;

class Debug
{
public:
	//static void DrawColliderOutline(const BoxCollider& collider, const Color& color);
	//static void DrawColliderOutline(const CircleCollider& collider, const Color& color);
	static void DrawLine(const Vector2& start, const Vector2& end, const Color& color);

	static inline void Log(std::string message) { std::cout << message << std::endl; }
	static void LogWarning(std::string message);
	static void LogError(std::string message);


	static inline void SetRenderer(SDL_Renderer* _renderer) { renderer = _renderer; }

private:
	static SDL_Renderer* renderer;
};

