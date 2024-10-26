#include "BoxCollider.h"

BoxCollider::BoxCollider(GameObject* _gameObject) : Collider(_gameObject), width(0.0f), height(0.0f)
{
	// INFO: Set the collider type to Box
	colliderType = Collider::Type::Box;
}
