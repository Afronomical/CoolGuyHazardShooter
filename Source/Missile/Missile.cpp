#include "Missile.h"


Missile::Missile()
{
	missileTexture = AssetHandler::LoadTexture("Assets/Animations/catgun.png");
	transform.lock()->position = Vector2(200, 200);
	transform.lock()->size = Vector2(300, 300);
}

Missile::~Missile()
{

}

void Missile::Update(float deltaTime)
{

}

void Missile::Draw()
{
	AssetHandler::DrawStatic(missileTexture, transform.lock()->position, transform.lock()->size.X, transform.lock()->size.Y, 1);
}

void Missile::MissileMove()
{

}

Vector2 Missile::directionToPlayer()
{
	Vector2 dir = target - transform.lock()->position;
	return dir;
}
