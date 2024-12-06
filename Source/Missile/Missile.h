#pragma once
#include "../Components/Component.h"
#include "../AssetLoading/AssetHandler.h"
#include "../Time/Time.h"
#include "../Physics/Rigidbody.h"
#include "../GameObject/GameObject.h"
#include "../Components/Transform.h"
#include "../Collision/BoxCollider.h"
#include "../Input/InputHandler.h"
#include "../Debugging/Debug.h"
#include "../Game/Game.h"
class Missile : public GameObject
{
public:
	Missile();
	~Missile();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void MissileMove();

	Vector2 target;

	Asset missileTexture;

	float turnSpeed = 1;
	float missileSpeed = 1;
	float distanceToPlayer;
	Vector2 directionToPlayer();

};

