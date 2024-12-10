#pragma once

#include "../Components/Component.h"
#include "../AssetLoading/AssetHandler.h"
#include "../Time/Time.h"
#include "../GameObject/GameObject.h"
#include "../Components/Transform.h"
#include "../Collision/BoxCollider.h"
#include "../Collision/MapCollisionResult.h"
#include "../Animation/Animator.h"
#include "../Particles/Emitter.h"
#include "../Player/Player.h"
#include "../Debugging/Debug.h"
//#include "../Enemies/WalkingEnemy.h"

class BaseEnemy : public GameObject
{
public:
	BaseEnemy();
	~BaseEnemy() override;

	virtual void Draw() override;

	void TakeDamage(int damage = 1);
	virtual void OnCollisionStay(std::shared_ptr<Collider> other) override;

protected:
	float health = 1;

	float animSpeed = 1;
	Vector2 animFrames = { 1, 1 };
	bool flipSprite;

	Asset texture;
	std::weak_ptr<BoxCollider> collider;
};