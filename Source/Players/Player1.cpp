#include "Player1.h"

Player1::Player1()
{
	GameObject::Handler::RegisterGameObject(this);
	texture = AssetHandler::LoadTexture("Assets/Animations/sonic.png");
	transform.lock()->position = Vector2(300, 320);
}

Player1::~Player1()
{

}

void Player1::Update(float deltaTime)
{
	deltaTimeRef = deltaTime;
	InputHandler::BindKeyToAction(SDL_SCANCODE_A, BindData(std::bind(&Player1::MoveLeft, this), ButtonState::Held));
	InputHandler::BindKeyToAction(SDL_SCANCODE_D, BindData(std::bind(&Player1::MoveRight, this), ButtonState::Held));
	InputHandler::BindKeyToAction(SDL_SCANCODE_SPACE, BindData(std::bind(&Player1::Jump, this), ButtonState::Pressed));
}

void Player1::Draw()
{
	AssetHandler::DrawAnimation(
		texture,
		transform.lock()->position,
		transform.lock()->size.X,
		transform.lock()->size.Y,
		1, 1);
}

void Player1::MoveLeft()
{
	transform.lock()->position.X -= playerMoveSpeed * deltaTimeRef;
}

void Player1::MoveRight()
{
	transform.lock()->position.X += playerMoveSpeed * deltaTimeRef;
}

void Player1::Jump()
{
	Debug::Log("Player 1 has Jumped");
}
