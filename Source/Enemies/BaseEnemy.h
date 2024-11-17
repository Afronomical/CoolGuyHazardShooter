#pragma once

#include "../Components/Component.h"
#include "../AssetLoading/AssetHandler.h"
#include "../Time/Time.h"
#include "../GameObject/GameObject.h"
#include "../Components/Transform.h"
#include "../Collision/BoxCollider.h"
#include "../Animation/Animator.h"

class BaseEnemy : public GameObject
{
public:
	BaseEnemy();
	~BaseEnemy() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	float health = 1;

	float animSpeed = 1;
	Vector2 animFrames = { 1, 1 };

	Asset texture;
	std::weak_ptr<BoxCollider> collider;
	//aAnimator anim;

	float moveSpeed = 10.0f;

	bool walkingLeft;
};

/*
Move x
check x col
if true then revert x

move y
check y col
if true then revert y
*/