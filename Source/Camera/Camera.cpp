#include "Camera.h"

Camera::Camera(int width, int height) : viewport({ 0, 0, width, height }), viewportExtension({ 50, 50 })
{
}

bool Camera::IsInView(const SDL_Rect& rect) const
{
	// INFO: Check using AABB between the camera viewport and the rectangle

	// INFO: Get the min and max values for the viewport (with its extension) and the rectangle
	int vpMinX = viewport.x - viewportExtension.X;
	int vpMaxX = viewport.x + viewport.w + viewportExtension.X;

	int vpMinY = viewport.y - viewportExtension.Y;
	int vpMaxY = viewport.y + viewport.h + viewportExtension.Y;

	int rectMinX = rect.x;
	int rectMaxX = rect.x + rect.w;

	int rectMinY = rect.y;
	int rectMaxY = rect.y + rect.h;

	// INFO: Check if the rectangle is within the viewport
	if (rectMaxX >= vpMinX && rectMinX <= vpMaxX && rectMaxY >= vpMinY && rectMinY <= vpMaxY)
	{
		// INFO: The rectangle is within the viewport
		return true;
	}

	// INFO: The rectangle is not within the viewport
	return false;
}
