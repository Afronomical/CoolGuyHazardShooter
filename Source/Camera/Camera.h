#pragma once

#include <SDL.h>
#include "../GameObject/GameObject.h"

#include "../Vector2/Vector2.h"

enum ECameraMode
{
	Static,
	FollowTarget,
	MoveToBorder,
};
class Camera : public GameObject
{
public:

	ECameraMode camMode;

	Camera(int width, int height);
	Camera(int width, int height, ECameraMode camMode);

	inline SDL_Rect GetViewport() const { return viewport; }

	/// @brief Checks if a rectangle is within the camera viewport
	/// @param rect : The rectangle to check against the camera viewport
	bool IsInView(const SDL_Rect& rect) const;
	std::weak_ptr<Transform> offset;
	Vector2 position;
	void SetTarget(std::weak_ptr<Transform>);
private:
	SDL_Rect viewport;
	Vector2 viewportExtension; // INFO: Extension amount in pixels for the viewport
};