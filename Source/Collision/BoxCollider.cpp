#include "BoxCollider.h"

BoxCollider::BoxCollider(GameObject* _gameObject, bool useCustomFunctions) : Collider(_gameObject, useCustomFunctions), width(0.0f), height(0.0f)
{
	// INFO: Set the collider type to Box
	colliderType = Collider::Type::Box;
}
