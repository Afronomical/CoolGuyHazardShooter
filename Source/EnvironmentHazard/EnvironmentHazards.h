#pragma once

#include "../AssetLoading/AssetHandler.h"
#include "../Time/Time.h"
#include "../GameObject/GameObject.h"
#include "../Components/Transform.h"
#include "../Collision/BoxCollider.h"
#include "../Collision/MapCollisionResult.h"
#include "../Animation/Animator.h"
#include "../Particles/Emitter.h"
#include "../Player/Player.h"


class EnvironemtHazard : public GameObject
{
public:
	EnvironemtHazard();
	~EnvironemtHazard() override;
	virtual void Draw() override;
	void OnCollisionEnter(std::shared_ptr<Collider> other) override;
	
	

protected:

	Asset AcidPoolTexture;
	std::weak_ptr<Rigidbody> AcidPoolRigidBody;
	std::weak_ptr<BoxCollider> AcidPoolCollider;
};