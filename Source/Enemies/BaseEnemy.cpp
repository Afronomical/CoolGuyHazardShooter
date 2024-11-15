#include "BaseEnemy.h"

BaseEnemy::BaseEnemy() : GameObject()
{
	//collider = AddComponent<BoxCollider>(this);
	texture = AssetHandler::LoadTexture("Assets/Animations/sonic.png");
	transform.lock()->position = Vector2(400, 320);

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
	if (walkingLeft)
		transform.lock()->position.X += -moveSpeed * deltaTime;

	//anim.Update();
}

void BaseEnemy::Draw()
{
	AssetHandler::DrawAnimation(
		texture,
		transform.lock()->position,
		size.X,
		size.Y,
		1.f,
		1.f);

	//anim.DrawCurrentFrame();
}