#include "Transform.h"

Transform::Transform(GameObject* _gameObject) : Component(_gameObject), position(Vector2::Zero), size(50, 50)
{
}

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