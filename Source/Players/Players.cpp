#include "Players.h"

//MIGHT GET CHANGED TO SPLIT TO 2 CLASSES!!!

Players::Players(GameObject* player1, GameObject* player2)
{
	/*GameObject::Handler::RegisterGameObject(player1);
	GameObject::Handler::RegisterGameObject(player2);

	texture = AssetHandler::LoadTexture("Assets/Animations/sonic.png");
	Player1->transform.lock()->position = Vector2(300, 320);
	Player2->transform.lock()->position = Vector2(500, 320);*/
}

Players::~Players()
{
	
}
/*
void Players::Update(float deltaTime) 
{
	if (InputHandler::GetKey(SDLK_a)) Debug::LogError("Moving Left");
}

void Players::MoveLeft(Transform* player)
{
	Debug::LogError("Moving Left");
}

void Players::MoveRight(Transform* player)
{
	Debug::LogError("Moving Right");
}

void Players::Jump(Transform* player)
{
	Debug::LogError("Jumping!");
}

void Players::Interact(Transform* player)
{

}

void Players::Draw()
{
	AssetHandler::DrawAnimation(
		texture,
		Player1->transform.lock()->position,
		Player1->transform.lock()->size.X,
		Player1->transform.lock()->size.Y,
		1, 1);

	
	AssetHandler::DrawAnimation(
		texture,
		Player2->transform.lock()->position,
		Player2->transform.lock()->size.X,
		Player2->transform.lock()->size.Y,
		1, 1);
}*/

