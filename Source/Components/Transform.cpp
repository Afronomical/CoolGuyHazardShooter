#include "Transform.h"

void Transform::Translate(const float x, const float y)
{
	position.X += x;
	position.Y += y;
}

void Transform::Translate(const Vector2& translation)
{
	position += translation;
}