#include "CircleCollider.h"

CircleCollider::CircleCollider(GameObject* _gameObject, bool useCustomFunctions) : Collider(_gameObject, useCustomFunctions), radius(0.0f)
{
	// INFO: Set the collider type to Circle
	colliderType = Collider::Type::Circle;
}
