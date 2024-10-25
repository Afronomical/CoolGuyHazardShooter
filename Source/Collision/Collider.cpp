#include "Collider.h"

void Collider::RemoveCollidingCollider(Collider* collider)
{
	// INFO: Iterates over colliding colliders ensuring the colliding collider is not nullptr
	// before removing the colliding collider that matches the passed in collider
	collidingColliders.erase(
		std::remove_if(
			collidingColliders.begin(),
			collidingColliders.end(),
			[&collider](Collider* collidingCollider) {
				return collidingCollider != nullptr && collidingCollider == collider;
			}
		),
		collidingColliders.end()
	);
}

bool Collider::ContainsCollidingCollider(Collider* collider) const
{
	// INFO: Iterates over colliding colliders ensuring both colliders exist before
	// checking if the colliding collider matches the passed in collider
	for (auto& collidingCollider : collidingColliders)
	{
		if (collidingCollider != nullptr && collidingCollider == collider)
			return true;
	}
	return false;
}
