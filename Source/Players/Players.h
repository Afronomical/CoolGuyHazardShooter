#pragma once
#include "../Components/Component.h"
#include "../AssetLoading/AssetHandler.h"
#include "../Time/Time.h"
#include "../GameObject/GameObject.h"
#include "../Components/Transform.h"
#include "../Collision/BoxCollider.h"
#include "../Input/InputHandler.h"


class Players
{
public:
	Players();
	~Players();


	void MoveLeft();
	void MoveRight();
	void Jump();
	void Interact();

	bool playerIsDead;
	float playersSpeed;
};

