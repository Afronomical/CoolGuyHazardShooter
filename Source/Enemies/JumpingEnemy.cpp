#include "JumpingEnemy.h"

JumpingEnemy::JumpingEnemy() : BaseEnemy()
{
	rb = AddComponent<Rigidbody>(this);
	rb.lock()->SetMass(mass);
	rb.lock()->SetGravity(gravity);
	transform.lock()->position = Vector2(600, 370);
	texture = AssetHandler::LoadTexture("Assets/Animations/sonic.png");
	jumpTimer = timeBetweenJumps;
	//TakeDamage();  // KILL THE ENEMY AT THE START
}

JumpingEnemy::~JumpingEnemy()
{
}

void JumpingEnemy::Update(float deltaTime)
{
	CheckMapCollisions();

	jumpTimer -= deltaTime;
	if (jumpTimer <= 0)
	{
		//jumpTimer = timeBetweenJumps;
		//rb.lock()->AddForce(0, jumpHeight, ForceMode::Impulse);
		//rb.lock()->SetGravity(Maths::Lerp(0, 100, deltaTime / jumpHeight, LerpEasing::EaseIn));
	}


	rb.lock()->Update(deltaTime);
	transform.lock()->Translate(0.0f, rb.lock()->GetDisplacement().Y);
	collider.lock()->UpdateCollider(transform.lock()->position);
}

void JumpingEnemy::CheckMapCollisions()
{
	if (Collider::Handler::CheckMapCollision(transform.lock()->position, transform.lock()->size.X, transform.lock()->size.Y))
	{
		rb.lock()->SetVelocity(Vector2{ 0, 0 });
	}
}