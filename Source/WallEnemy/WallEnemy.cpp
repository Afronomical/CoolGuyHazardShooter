#include "WallEnemy.h"


WallEnemy::WallEnemy()
{
	wallTexture = AssetHandler::LoadTexture("Assets/Animations/rb_305.png");
}

WallEnemy::~WallEnemy()
{

}

void WallEnemy::Update(float deltaTime)
{
	transform.lock()->position.Y -= wallMoveSpeed * deltaTime;
}

void WallEnemy::Draw()
{
	AssetHandler::DrawAnimation(wallTexture, transform.lock()->position, transform.lock()->size.X, transform.lock()->size.Y, 1, 1);
}
