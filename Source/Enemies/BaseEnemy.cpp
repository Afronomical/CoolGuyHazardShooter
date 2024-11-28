#include "BaseEnemy.h"

BaseEnemy::BaseEnemy() : GameObject()
{
	collider = AddComponent<BoxCollider>(this);
	texture = AssetHandler::LoadTexture("Assets/Animations/sonic.png");
	transform.lock()->position = Vector2(400, 370);
	walkingLeft = false;

	/*anim;
	anim.SetAnimatorValues
	(
		"Assets/Animations/sonic.png",
		transform.lock()->position,
		10,
		8,
		4,
		62,
		60,
		0.2f
	);*/
}

BaseEnemy::~BaseEnemy()
{

}

void BaseEnemy::Update(float deltaTime)
{
	int moveDir = walkingLeft ? -1 : 1;

	transform.lock()->position.X += moveSpeed * moveDir * deltaTime;

	//anim.Update();
}

void BaseEnemy::Draw()
{
	AssetHandler::DrawAnimation(
		texture,  // Texture
		transform.lock()->position,  // Position
		transform.lock()->size.X,  // Width
		transform.lock()->size.Y,  // Height
		1,  // Row
		1,  // Frame
		1,  // Scroll Speed
		1,  // Scale,
		walkingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE  // Flip
		);

	//anim.DrawCurrentFrame();
}

void BaseEnemy::CheckMapCollisions()
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