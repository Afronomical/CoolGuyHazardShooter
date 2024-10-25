#pragma once
//#include "BoxCollider.h"
//#include "CircleCollider.h"
#include <string>
#include "SDL_render.h"
#include "../Vector2/Vector2.h"

struct Color
{
public:

	Uint8 R;
	Uint8 G;
	Uint8 B;
	Uint8 A;

	Color(Uint8 _R, Uint8 _G, Uint8 _B, Uint8 _A) : R(_R), G(_G), B(_B), A(_A) {}

	Color RandomColor(Uint8 A)
	{
		return Color(rand() % 255, rand() % 255, rand() % 255, A);
	}

 	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Yellow;
	static const Color Orange;
	static const Color Purple;
	static const Color White;
	static const Color Black;

};

const Color Color::Red = Color(255, 0, 0, 255);
const Color Color::Green = Color(0, 255, 0, 255);
const Color Color::Blue = Color(0, 0, 255, 255);
const Color Color::Yellow = Color(255, 255, 0, 255);
const Color Color::Orange = Color(255, 165, 0, 255);
const Color Color::Purple = Color(128, 0, 128, 255);
const Color Color::White = Color(255, 255, 255, 255);
const Color Color::Black = Color(0, 0, 0, 255);

static class Debug
{

private:
	static SDL_Renderer* renderer;

public:
	//static void DrawColliderOutline(const BoxCollider& collider, const Color& color);
	//static void DrawColliderOutline(const CircleCollider& collider, const Color& color);

	static void Log(std::string message);
	static void LogWarning(std::string message);
	static void LogError(std::string message);

	static void DrawLine(const Vector2& start, const Vector2& end, const Color& color);

	static void SetRenderer(SDL_Renderer* _renderer);
};

