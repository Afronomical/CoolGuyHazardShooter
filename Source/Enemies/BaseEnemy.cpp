#include "BaseEnemy.h"

BaseEnemy::BaseEnemy() : GameObject()
{
	collider = AddComponent<BoxCollider>(this, true);
	collider.lock()->SetOnCollisionEnter(std::bind(&BaseEnemy::PlayerColliderOnCollisionEnter, this, std::placeholders::_1));
	collider.lock()->SetWidth(5);
	collider.lock()->SetHeight(5);

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


void BaseEnemy::Draw()
{
	AssetHandler::DrawAnimation(
		texture,  // Texture
		transform.lock()->position,  // Position
		transform.lock()->size.X,  // Width
		transform.lock()->size.Y,  // Height
		1,  // Row
		1,  // Frame
		1,  // Scroll Speed
		health,  // Scale  <---- TEMPORARY, CHANGE THIS
		flipSprite ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE  // Flip
		);

	//anim.DrawCurrentFrame();
}


void BaseEnemy::TakeDamage(int damage)
{
	if (health > 0)
		health -= damage;  // Hurt the enemy

	if (health <= 0)  // Death
	{
		//emitter.lock()->EmitParticles(  // Death particles
		//	3,
		//	3,
		//	texture,
		//	transform.lock()->position
		//);
	}
}


void BaseEnemy::PlayerColliderOnCollisionEnter(std::shared_ptr<Collider> other)
{
	Player* p = static_cast<Player*>(other->GetGameObject());
	if (p != nullptr)
	{
		p->SlowDown();
	}
}