#pragma once
#include <SDL.h>

//initial setup
class Camera 
{
public:
	Camera(int width, int height);
	SDL_Rect getViewport();
	//future functions for camera to be added

private:
	int width;
	int height;
	SDL_Rect viewport;
};