#include "WalkingEnemy.h"

WalkingEnemy::WalkingEnemy() : BaseEnemy()
{
	transform.lock()->position = Vector2(400, 370);
	//texture = AssetHandler::LoadTexture("Assets/Animations/sonic.png");
	walkingLeft = false;
	alwaysUpdate = true;
	
	
	animController.lock()->AddAnimation("Walk", "Assets/Animations/AcidPool.png", transform.lock()->position, 10, 7, 4, 400, 400, 1.0f);
	animController.lock()->SetCurrentAnimation("Walk");
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
	animController.lock()->Update();
	animController.lock()->Draw();
}

void WalkingEnemy::Start()
{
	

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
