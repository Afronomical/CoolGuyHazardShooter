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

class WallEnemy :  public GameObject
{

public:
	WallEnemy();
	~WallEnemy();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void PlayerTriggerEnter(std::shared_ptr<Collider> other);

	Asset wallTexture;

	std::weak_ptr<Rigidbody> wallRigidBody;
	std::weak_ptr<BoxCollider> wallCollider;

	float wallMoveSpeed = 10;
	float acceleration = 0.05f;
};

