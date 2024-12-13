#include "BaseEnemy.h"

BaseEnemy::BaseEnemy() : GameObject()
{
	collider = AddComponent<BoxCollider>(this);
	collider.lock()->SetWidth(50);
	collider.lock()->SetHeight(50);

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
	if (debugCollision) Debug::DrawColliderOutline(collider.lock(), Color::Orange);

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


void BaseEnemy::OnCollisionStay(std::shared_ptr<Collider> other)
{
	if (Player* p = dynamic_cast<Player*>(other->GetGameObject()))
	{
		p->SlowDown();
	}
	//if (WalkingEnemy* e = dynamic_cast<WalkingEnemy*>(other->GetGameObject()))
	//{
	//	e->TurnAround();
	//}
}