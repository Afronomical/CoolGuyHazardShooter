#pragma once

#include <SDL.h>

#include "../Vector2/Vector2.h"

class Camera 
{
public:
	Camera(int width, int height);

	inline SDL_Rect GetViewport() const { return viewport; }

	/// @brief Checks if a rectangle is within the camera viewport
	/// @param rect : The rectangle to check against the camera viewport
	bool IsInView(const SDL_Rect& rect) const;

private:
	SDL_Rect viewport;
	Vector2 viewportExtension; // INFO: Extension amount in pixels for the viewport
};