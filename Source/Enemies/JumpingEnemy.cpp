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

	jumpCooldown -= deltaTime;
	if (jumpCooldown <= 0)
	{
		jumpTimer = 0;
		jumpCooldown = timeBetweenJumps;
		//rb.lock()->AddForce(0, jumpHeight, ForceMode::Impulse);
		//rb.lock()->SetGravity(Maths::Lerp(0, 100, deltaTime / jumpHeight, LerpEasing::EaseIn));
	}

	if (jumpTimer >= 0 && jumpTimer < jumpTime)
	{
		jumpTimer += deltaTime;

		if (jumpTimer < jumpTime / 2)
			rb.lock()->SetGravity(Maths::Lerp(0, 100, jumpTime / 2 / jumpTimer, LerpEasing::EaseIn));
		else
			rb.lock()->SetGravity(Maths::Lerp(100, 0, jumpTime / 2 / jumpTimer, LerpEasing::EaseOut));
	}
	else
		rb.lock()->SetGravity(0);

	if (transform.lock()->position.Y >= 370)
		transform.lock()->position.Y = 370;


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