#include "Player.h"

#include "../AssetLoading/AssetHandler.h"
#include "../Components/Transform.h"
#include "../Input/InputHandler.h"
#include "../Debugging/Debug.h"

#include "../Collision/MapCollisionResult.h"


Player::Player(bool isPlayer1)
{
	//GameObject::Handler::RegisterGameObject(this);
	texture = AssetHandler::LoadTexture("Assets/Animations/sonic.png");
	playerRigidBody = AddComponent<Rigidbody>(this);
	playerCollider = AddComponent<BoxCollider>(this);

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

/*void Player::Start()
{
	enemyColliderRef = enemy->GetComponent<BoxCollider>();
}*/

void Player::Update(float deltaTime)
{
	playerRigidBody.lock()->Update(deltaTime);
	//transform.lock()->Translate(0.0f, -playerRigidBody.lock()->GetDisplacement().Y);

	//if(!isGrounded) transform.lock()->position.Y += playerRigidBody.lock()->GetGravity() * deltaTime * fallSpeed;
	
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
	
	/*if (transform.lock()->position.Y >= 360)
	{
		transform.lock()->position.Y = 360;
		playerRigidBody.lock()->SetVelocity(0);
	}

	if (transform.lock()->position.Y <= playerJumpHeightLimit)
	{
		playerRigidBody.lock()->SetVelocity(0);
		playerRigidBody.lock()->AddForce(0, 0, ForceMode::None);
	}*/

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
	if (isGrounded) 
	{
		//isGrounded = false;
		//isJumping = true;
		//playerRigidBody.lock()->AddForce(0, playerJumpForce, ForceMode::Impulse);
		//transform.lock()->position.Y -= playerJumpForce * deltaTimeRef;
	}
}

void Player::Kill()
{
	Debug::Log("Player has died");
	Destroy();
}

void Player::SlowDown()
{
	playerMoveSpeed -= slowedAmount;
	playerJumpForce -= slowedAmount;
}

/*void Player::OnCollisionEnter(Collider* other)
{
	if (other == enemyColliderRef) 
	{

	}
}*/





