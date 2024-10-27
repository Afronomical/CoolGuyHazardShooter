#pragma once

#include <SDL_stdinc.h>

#include <stdlib.h>

struct Color
{
public:
	Uint8 R;
	Uint8 G;
	Uint8 B;
	Uint8 A;

	Color(Uint8 _R = 255, Uint8 _G = 255, Uint8 _B = 255, Uint8 _A = 255) : R(_R), G(_G), B(_B), A(_A) {}

	static inline Color RandomColor(Uint8 A) { return Color(rand() % 255, rand() % 255, rand() % 255, A); }

	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Yellow;
	static const Color Orange;
	static const Color Purple;
	static const Color White;
	static const Color Black;

};

