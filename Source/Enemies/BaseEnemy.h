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

class BaseEnemy : public GameObject
{
public:
	BaseEnemy();
	~BaseEnemy() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void TakeDamage(int damage = 1);
	void PlayerColliderOnCollisionEnter(std::shared_ptr<Collider> other);

protected:
	float health = 1;

	float animSpeed = 1;
	Vector2 animFrames = { 1, 1 };

	Asset texture;
	std::weak_ptr<BoxCollider> collider;

	float moveSpeed = 10.0f;

	bool walkingLeft;

	void CheckMapCollisions();
};

/*
Move x
check x col
if true then revert x

move y
check y col
if true then revert y
*/