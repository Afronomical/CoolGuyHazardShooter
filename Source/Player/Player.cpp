#include "Player.h"

#include "../AssetLoading/AssetHandler.h"
#include "../Components/Transform.h"
#include "../Input/InputHandler.h"
#include "../Debugging/Debug.h"
#include "../Collision/Collider.h"
#include "../Collision/MapCollisionResult.h"

Player::Player(bool isPlayer1)
{
	//GameObject::Handler::RegisterGameObject(this);
	texture = AssetHandler::LoadTexture("Assets/Animations/sonic.png");
	transform.lock()->position = Vector2(300, 360);

	// INFO: Temporary bool to ensure only player 1 moves with the W and S keys in the update function
	this->isPlayer1 = isPlayer1;

	if (isPlayer1)
	{
		InputHandler::BindKeyToAction(SDL_SCANCODE_A, BindData(std::bind(&Player::MoveLeft, this), ButtonState::Held));
		InputHandler::BindKeyToAction(SDL_SCANCODE_D, BindData(std::bind(&Player::MoveRight, this), ButtonState::Held));
		InputHandler::BindKeyToAction(SDL_SCANCODE_W, BindData(std::bind(&Player::Jump, this), ButtonState::Pressed));
	}
	else
	{
		InputHandler::BindKeyToAction(SDL_SCANCODE_LEFT, BindData(std::bind(&Player::MoveLeft, this), ButtonState::Held));
		InputHandler::BindKeyToAction(SDL_SCANCODE_RIGHT, BindData(std::bind(&Player::MoveRight, this), ButtonState::Held));
		InputHandler::BindKeyToAction(SDL_SCANCODE_UP, BindData(std::bind(&Player::Jump, this), ButtonState::Pressed));
	}
}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{
	deltaTimeRef = deltaTime;

	// INFO: Check if the player has collided with the map and log extra detailed results
	MapCollisionResult collisionResult;

	if (Collider::Handler::CheckMapCollision(transform.lock()->position, transform.lock()->size.X, transform.lock()->size.Y, &collisionResult) && isPlayer1)
	{
		// INFO: Used for AI detection so enemies don't fall off ledges
		if (!collisionResult.isCollidingRightTile)
		{
			Debug::Log("There is ledge on right");
		}

		if (!collisionResult.isCollidingLeftTile)
		{
			Debug::Log("There is ledge on left");
		}
	}

	// INFO: Temporary logic to move player down to floor tiles to test ledge detection
	if (isPlayer1)
	{
		if (InputHandler::GetKey(SDL_SCANCODE_W))
		{
			transform.lock()->position.Y -= playerMoveSpeed * deltaTime;
		}

		if (InputHandler::GetKey(SDL_SCANCODE_S))
		{
			transform.lock()->position.Y += playerMoveSpeed * deltaTime;
		}
	}
}

void Player::Draw()
{
	AssetHandler::DrawAnimation(
		texture,
		transform.lock()->position,
		transform.lock()->size.X,
		transform.lock()->size.Y,
		1, 1);
}

void Player::MoveLeft()
{
	transform.lock()->position.X -= playerMoveSpeed * deltaTimeRef;
}

void Player::MoveRight()
{
	transform.lock()->position.X += playerMoveSpeed * deltaTimeRef;
}

void Player::Jump()
{
	Debug::Log("Player 1 has Jumped");
}

void Player::Kill()
{
	Debug::Log("Player has died");
}