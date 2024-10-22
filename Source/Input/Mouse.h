#pragma once

#include <SDL.h>

struct Mouse
{
	Mouse() : mouseData() {};

	inline void SetMouseData(SDL_Rect _mouseData) { mouseData = _mouseData; }
	inline void SetMouseData(int x, int y, int width, int height) { mouseData = { x, y, width, height }; }
	
	SDL_Rect mouseData;
};