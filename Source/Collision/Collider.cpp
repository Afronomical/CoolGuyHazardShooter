#include "Collider.h"

#include "BoxCollider.h"
#include "CircleCollider.h"
#include "../Debugging/MemoryLeakDetector.h"
#include "../GameObject/GameObject.h"

#pragma region StaticHandlerMembers
std::vector<std::weak_ptr<Collider>> Collider::Handler::colliders;
#pragma endregion StaticHandlerMembers

#pragma region HandlerMethods
void Collider::Handler::CheckCollisions()
{
	// INFO: Compares each collider with every other collider in the vector
	for (size_t i = 0; i < colliders.size(); i++)
	{
		for (size_t j = i + 1; j < colliders.size(); j++)
		{
			// INFO: Create temporary shared pointers to the colliders
			auto collider1 = colliders[i].lock();
			auto collider2 = colliders[j].lock();

			// INFO: Circle & Circle
			if (collider1->GetColliderType() == Collider::Type::Circle && collider2->GetColliderType() == Collider::Type::Circle)
			{
				CircleCircleCollision(std::dynamic_pointer_cast<CircleCollider>(collider1), std::dynamic_pointer_cast<CircleCollider>(collider2));
			}
			// INFO: Box & Box
			else if (collider1->GetColliderType() == Collider::Type::Box && collider2->GetColliderType() == Collider::Type::Box)
			{
				BoxBoxCollision(std::dynamic_pointer_cast<BoxCollider>(collider1), std::dynamic_pointer_cast<BoxCollider>(collider2));
			}
			// INFO: Circle & Box
			else if (collider1->GetColliderType() == Collider::Type::Circle && collider2->GetColliderType() == Collider::Type::Box)
			{
				CircleBoxCollision(std::dynamic_pointer_cast<CircleCollider>(collider1), std::dynamic_pointer_cast<BoxCollider>(collider2));
			}
			// INFO: Box & Circle
			else if (collider1->GetColliderType() == Collider::Type::Box && collider2->GetColliderType() == Collider::Type::Circle)
			{
				CircleBoxCollision(std::dynamic_pointer_cast<CircleCollider>(collider2), std::dynamic_pointer_cast<BoxCollider>(collider1));
			}
		}
	}
}

void Collider::Handler::CircleCircleCollision(std::shared_ptr<CircleCollider> c1, std::shared_ptr<CircleCollider> c2)
{
	// INFO: Circle centre positions
	Vector2 c1CentrePos = c1->GetCentrePosition();
	Vector2 c2CentrePos = c2->GetCentrePosition();

	// INFO: Calculate the difference between the two circles
	float dx = c1CentrePos.X - c2CentrePos.X;
	float dy = c1CentrePos.Y - c2CentrePos.Y;

	// INFO: The sum of the radii of the two circles
	float totalRadius = c1->GetRadius() + c2->GetRadius();

	// INFO: Flag to check if the colliders have collided
	bool hasCollided = false;

	// INFO: Check if the distance between the two circles is less than the sum of their radii
	if ((dx * dx) + (dy * dy) < totalRadius * totalRadius)
	{
		hasCollided = true;
	}

	// INFO: Handle the collision response
	HandleCollisionResponse(c1, c2, hasCollided);
}

void Collider::Handler::BoxBoxCollision(std::shared_ptr<BoxCollider> b1, std::shared_ptr<BoxCollider> b2)
{
	// INFO: Get box 1 and 2 positions
	Vector2 b1Pos = b1->GetPosition();
	Vector2 b2Pos = b2->GetPosition();

	// INFO: The min and max x and y values of the first box collider
	float b1MinX = b1Pos.X;
	float b1MaxX = b1Pos.X + b1->GetWidth();

	float b1MinY = b1Pos.Y;
	float b1MaxY = b1Pos.Y + b1->GetHeight();

	// INFO: The min and max x and y values of the second box collider
	float b2MinX = b2Pos.X;
	float b2MaxX = b2Pos.X + b2->GetWidth();

	float b2MinY = b2Pos.Y;
	float b2MaxY = b2Pos.Y + b2->GetHeight();

	// INFO: Flag to check if the colliders have collided
	bool hasCollided = false;

	// INFO: Check for overlap between the two box colliders
	if (b1MaxX > b2MinX && b1MinX < b2MaxX && b1MaxY > b2MinY && b1MinY < b2MaxY)
	{
		hasCollided = true;
	}

	// INFO: Handle the collision response
	HandleCollisionResponse(b1, b2, hasCollided);
}

void Collider::Handler::CircleBoxCollision(std::shared_ptr<CircleCollider> c, std::shared_ptr<BoxCollider> b)
{
	// INFO: Initialize variables used to determine collision
	float closestX = 0;
	float closestY = 0;

	// INFO: Get the centre position and radius of the circle
	Vector2 cCentrePos = c->GetCentrePosition();
	float cRadius = c->GetRadius();

	// INFO: Get box position
	Vector2 bPos = b->GetPosition();

	// INFO: Get the min and max x and y values of the box collider
	float bMinX = bPos.X;
	float bMaxX = bPos.X + b->GetWidth();

	float bMinY = bPos.Y;
	float bMaxY = bPos.Y + b->GetHeight();

	// INFO: Find the closest x value to the circles' centre x
	if (cCentrePos.X < bMinX)
	{
		closestX = bMinX;
	}
	else if (cCentrePos.X > bMaxX)
	{
		closestX = bMaxX;
	}
	else
	{
		closestX = cCentrePos.X;
	}

	// INFO: Find the closest y value to the circles' centre y
	if (cCentrePos.Y < bMinY)
	{
		closestY = bMinY;
	}
	else if (cCentrePos.Y > bMaxY)
	{
		closestY = bMaxY;
	}
	else
	{
		closestY = cCentrePos.Y;
	}

	// INFO: The difference between the circle's centre and the closest x and y values
	float dx = cCentrePos.X - closestX;
	float dy = cCentrePos.Y - closestY;

	// INFO: Flag to check if the colliders have collided
	bool hasCollided = false;

	// INFO: Check if the distance between the circle and closest x and y values is less than the circle's radius
	if ((dx * dx) + (dy * dy) < cRadius * cRadius)
	{
		hasCollided = true;
	}

	// INFO: Handle the collision response
	HandleCollisionResponse(c, b, hasCollided);
}

void Collider::Handler::HandleCollisionResponse(std::shared_ptr<Collider> c1, std::shared_ptr<Collider> c2, bool hasCollided)
{
	if (hasCollided)
	{
		// INFO: C1 Checks
		if (c2->ContainsCollidingCollider(c1))
		{
			// INFO: Given that c2 contains c1, we know that c1 is staying in contact with c2

			// INFO: If the collider is a trigger, call trigger equivalent function else call collision equivalent function
			if (c1->IsTrigger())
				c1->OnTriggerStay(c2);
			else
				c1->OnCollisionStay(c2);
		}
		else
		{
			// INFO: Given that the two colliders are colliding, but c2 does not contain c1,
			// we know that c1 has just collided with c2
			c2->AddCollidingCollider(c1);

			// INFO: If the collider is a trigger, call trigger equivalent function else call collision equivalent function
			if (c1->IsTrigger())
				c1->OnTriggerEnter(c2);
			else
				c1->OnCollisionEnter(c2);
		}

		// INFO: C2 Checks
		if (c1->ContainsCollidingCollider(c2))
		{
			// INFO: Given that c1 contains c2, we know that c2 is staying in contact with c1

			// INFO: If the collider is a trigger, call trigger equivalent function else call collision equivalent function
			if (c2->IsTrigger())
				c2->OnTriggerStay(c1);
			else
				c2->OnCollisionStay(c1);
		}
		else
		{
			// INFO: Given that the two colliders are colliding, but c1 does not contain c2,
			// we know that c2 has just collided with c1
			c1->AddCollidingCollider(c2);

			// INFO: If the collider is a trigger, call trigger equivalent function else call collision equivalent function
			if (c2->IsTrigger())
				c2->OnTriggerEnter(c1);
			else
				c2->OnCollisionEnter(c1);
		}
	}
	else
	{
		// INFO: C1 Checks
		if (c2->ContainsCollidingCollider(c1))
		{
			// INFO: Given that the two colliders are NOT colliding, yet c2 contains c1, we know 
			// that c1 has just stopped colliding with c2
			c2->RemoveCollidingCollider(c1);

			// INFO: If the collider is a trigger, call trigger equivalent function else call collision equivalent function
			if (c1->IsTrigger())
				c1->OnTriggerExit(c2);
			else
				c1->OnCollisionExit(c2);
		}

		// INFO: C2 Checks
		if (c1->ContainsCollidingCollider(c2))
		{
			// INFO: Given that the two colliders are NOT colliding, yet c1 contains c2, we know 
			// that c2 has just stopped colliding with c1
			c1->RemoveCollidingCollider(c2);

			// INFO: If the collider is a trigger, call trigger equivalent function else call collision equivalent function
			if (c2->IsTrigger())
				c2->OnTriggerExit(c1);
			else
				c2->OnCollisionExit(c1);
		}
	}
}

void Collider::Handler::UnregisterCollider(std::shared_ptr<Collider> collider)
{
	// INFO: Iterates over the colliders ensuring the collider is not nullptr before removing the collider
	colliders.erase(
		std::remove_if(
			colliders.begin(),
			colliders.end(),
			[&collider](std::weak_ptr<Collider> registeredCollider) {
				return !registeredCollider.expired() && registeredCollider.lock() == collider;
			}
		),
		colliders.end()
	);
}
#pragma endregion HandlerMethods

#pragma region ColliderMethods
Collider::Collider(GameObject* _gameObject, bool useCustomFunctions) : Component(_gameObject), colliderType(Type::None), position(Vector2()),
																	   offset(Vector2()), isTrigger(false)
{
	// INFO: Register the collider with the handler
	Collider::Handler::RegisterCollider(shared_from_this());

	// INFO: Allow multiple colliders to be added onto the same game object
	canHaveMultiple = true;
	
	// INFO: Set the collision functions to hold the owning game objects collision functions
	if (!useCustomFunctions)
	{
		OnCollisionEnter = std::bind(&GameObject::OnCollisionEnter, GetGameObject(), std::placeholders::_1);
		OnCollisionStay = std::bind(&GameObject::OnCollisionStay, GetGameObject(), std::placeholders::_1);
		OnCollisionExit = std::bind(&GameObject::OnCollisionExit, GetGameObject(), std::placeholders::_1);

		OnTriggerEnter = std::bind(&GameObject::OnTriggerEnter, GetGameObject(), std::placeholders::_1);
		OnTriggerStay = std::bind(&GameObject::OnTriggerStay, GetGameObject(), std::placeholders::_1);
		OnTriggerExit = std::bind(&GameObject::OnTriggerExit, GetGameObject(), std::placeholders::_1);
	}
}

void Collider::RemoveCollidingCollider(std::shared_ptr<Collider> collider)
{
	// INFO: Iterates over colliding colliders ensuring the colliding collider is not nullptr
	// before removing the colliding collider that matches the passed in collider
	collidingColliders.erase(
		std::remove_if(
			collidingColliders.begin(),
			collidingColliders.end(),
			[&collider](std::weak_ptr<Collider> collidingCollider) {
				return !collidingCollider.expired() && collidingCollider.lock() == collider;
			}
		),
		collidingColliders.end()
	);
}

bool Collider::ContainsCollidingCollider(std::shared_ptr<Collider> collider) const
{
	// INFO: Iterates over colliding colliders ensuring both colliders exist before
	// checking if the colliding collider matches the passed in collider
	for (auto& collidingCollider : collidingColliders)
	{
		if (!collidingCollider.expired() && collidingCollider.lock() == collider)
			return true;
	}
	return false;
}
#pragma endregion ColliderMethods
