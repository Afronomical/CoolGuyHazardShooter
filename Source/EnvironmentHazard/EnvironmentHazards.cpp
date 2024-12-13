#include "EnvironmentHazards.h"
#include "../Debugging/Debug.h"


EnvironemtHazard::EnvironemtHazard() : GameObject()
{
	AcidPoolTexture = AssetHandler::LoadTexture("Assets/Animations/AcidPool.png");
	AcidPoolCollider = AddComponent<BoxCollider>(this);
	transform.lock()->position = Vector2(500, 410);
	acidParticles = AddComponent<Emitter>(this, 100.0f);
	AcidPoolCollider.lock()->SetWidth(200);
	AcidPoolCollider.lock()->SetHeight(150);
}

EnvironemtHazard::~EnvironemtHazard()
{
}

void EnvironemtHazard::Draw()
{
	transform.lock()->size.X = 200;
	transform.lock()->size.Y = 100;
	AssetHandler::DrawStatic(AcidPoolTexture, transform.lock()->position, transform.lock()->size.X, transform.lock()->size.Y, 1);
	acidParticles.lock()->EmitParticles(50, 10.0f, AcidPoolTexture, transform.lock()->position);

	AcidPoolCollider.lock()->UpdateCollider(transform.lock()->position);
}

void EnvironemtHazard::OnCollisionStay(std::shared_ptr<Collider> other)
{
	if (Player* p = dynamic_cast<Player*>(other->GetGameObject()))
	{
		p->SlowDown(1.0f);
	}
}
