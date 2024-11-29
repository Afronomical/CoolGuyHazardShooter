#include "WallEnemy.h"


WallEnemy::WallEnemy()
{
	wallTexture = AssetHandler::LoadTexture("Assets/Animations/enemySquareTexture.png");
	//wallTexture = AssetHandler::LoadTexture("Assets/Animations/sonic.png");
	//wallRigidBody = AddComponent<Rigidbody>(this);
	transform.lock()->position = Vector2(0, 0);
	transform.lock()->size = Vector2(100, 500);
	wallCollider = AddComponent<BoxCollider>(this);
	wallCollider.lock()->SetIsTrigger(true);
	wallCollider.lock()->SetOnTriggerEnter(std::bind(&WallEnemy::PlayerTriggerEnter, this, std::placeholders::_1));
}

WallEnemy::~WallEnemy()
{

}

void WallEnemy::Update(float deltaTime)
{
	transform.lock()->position.X += wallMoveSpeed * deltaTime;
	//wallRigidBody.lock()->Update(deltaTime);
	wallMoveSpeed += acceleration;
	
}

void WallEnemy::Draw()
{
	//AssetHandler::DrawAnimation(wallTexture, transform.lock()->position, transform.lock()->size.X, transform.lock()->size.Y, 1, 1);

	AssetHandler::DrawStatic(wallTexture, transform.lock()->position, transform.lock()->size.X, transform.lock()->size.Y, 1);
}

void WallEnemy::PlayerTriggerEnter(std::shared_ptr<Collider> other)
{
	Debug::Log("Player hit wall");
} 
