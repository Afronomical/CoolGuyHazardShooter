#pragma once

#include "../Components/Component.h"
#include "../AssetLoading/AssetHandler.h"
#include "../Time/Time.h"
#include "../GameObject/GameObject.h"
#include "../Components/Transform.h"
#include "../Collision/BoxCollider.h"

class BaseEnemy : public GameObject
{
public:
	BaseEnemy();
	~BaseEnemy();

protected:
	float health = 1;
	Vector2 size = { 1, 1 };

	float animSpeed = 1;
	Vector2 animFrames = { 1, 1 };

	Asset* texture;
	std::weak_ptr<BoxCollider> collider;
};