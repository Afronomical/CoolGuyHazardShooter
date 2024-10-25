#include "Debug.h"
#include <iostream>

void Debug::Log(std::string message)
{
	std::cout << message << std::endl;
}

void Debug::LogWarning(std::string message)
{
	std::cout << message << std::endl;
}

void Debug::LogError(std::string message)
{
	std::cout << message << std::endl;
}

void Debug::DrawLine(const Vector2& start, const Vector2& end, const Color& color)
{
	SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
	SDL_RenderDrawLine(renderer, start.X, start.Y, end.X, end.Y);
}

void Debug::SetRenderer(SDL_Renderer* _renderer)
{
	renderer = _renderer;
}
