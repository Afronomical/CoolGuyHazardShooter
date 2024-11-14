#include "Transform.h"

void Transform::Translate(const float x, const float y)
{
	// INFO: Don't translate if component is not active
	if (!IsActive())
		return;

	position.X += x;
	position.Y += y;
}

void Transform::Translate(const Vector2& translation)
{
	// INFO: Don't translate if component is not active
	if (!IsActive())
		return;

	position += translation;
}