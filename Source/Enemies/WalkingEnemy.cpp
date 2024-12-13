#include "WalkingEnemy.h"

WalkingEnemy::WalkingEnemy() : BaseEnemy()
{
	transform.lock()->position = Vector2(400, 370);
	texture = AssetHandler::LoadTexture("Assets/Animations/sonic.png");
	walkingLeft = false;
	alwaysUpdate = true;
}

WalkingEnemy::~WalkingEnemy()
{
}

void WalkingEnemy::Update(float deltaTime)
{
	CheckMapCollisions();

	int moveDir = walkingLeft ? -1 : 1;

	transform.lock()->position.X += moveSpeed * moveDir * deltaTime;

	flipSprite = walkingLeft;

	collider.lock()->UpdateCollider(transform.lock()->position);
}

void WalkingEnemy::TurnAround()
{
	SetWalkingLeft(!walkingLeft);
}

void WalkingEnemy::CheckMapCollisions()
{
	MapCollisionResult collisionResult;

	if (Collider::Handler::CheckMapCollision(transform.lock()->position, transform.lock()->size.X, transform.lock()->size.Y, &collisionResult))
	{
		if (walkingLeft && !collisionResult.isCollidingLeftTile)  // If moving left and there is no tile to the bottom-left of you
		{
			walkingLeft = false;
		}

		else if (!walkingLeft && !collisionResult.isCollidingRightTile)  // If moving right and there is no tile to the bottom-right of you
		{
			walkingLeft = true;
		}
	}
}
