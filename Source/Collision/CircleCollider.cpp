#include "CircleCollider.h"

CircleCollider::CircleCollider(GameObject* _gameObject) : Collider(_gameObject), radius(0.0f)
{
	// INFO: Set the collider type to Circle
	colliderType = Collider::Type::Circle;
}
