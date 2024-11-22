#include "Player.h"

Player::Player(bool isPlayer1)
{
	//GameObject::Handler::RegisterGameObject(this);
	texture = AssetHandler::LoadTexture("Assets/Animations/sonic.png");
	transform.lock()->position = Vector2(300, 360);

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