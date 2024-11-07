#include "BaseEnemy.h"

BaseEnemy::BaseEnemy()
{
	collider = AddComponent<BoxCollider>(this);
	//texture = &AssetHandler::LoadTexture("");
}

BaseEnemy::~BaseEnemy()
{

}

//void GameObject::Update(float deltaTime) 
//{
//	Vector2 position = transform.lock()->position;
//	AssetHandler::DrawAnimation(
//		,
//		position, 
//		size, 
//		size);
//}