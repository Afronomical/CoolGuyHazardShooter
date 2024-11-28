#pragma once
#include "../Components/Component.h"
#include "../AssetLoading/AssetHandler.h"
#include "../Time/Time.h"
#include "../GameObject/GameObject.h"
#include "../Components/Transform.h"
#include "../Collision/BoxCollider.h"
#include "../Input/InputHandler.h"
#include "../Debugging/Debug.h"

class WallEnemy :  public GameObject
{

public:
	WallEnemy();
	~WallEnemy();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	Asset wallTexture;

	float wallMoveSpeed = 25;
};

