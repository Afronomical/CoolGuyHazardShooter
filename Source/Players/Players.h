#pragma once
#include "../Components/Component.h"
#include "../AssetLoading/AssetHandler.h"
#include "../Time/Time.h"
#include "../GameObject/GameObject.h"
#include "../Components/Transform.h"
#include "../Collision/BoxCollider.h"
#include "../Input/InputHandler.h"
#include "../Debugging/Debug.h"

class Players : public GameObject
{
public:
	//MIGHT GET CHANGED TO SPLIT TO 2 CLASSES!!!
	Players(GameObject* player1, GameObject* player2);
	~Players();
	/*
	Players* Player1;
	Players* Player2;
	Asset texture;

	void MoveLeft(Transform* player);
	void MoveRight(Transform* player);
	void Jump(Transform* player);
	void Interact(Transform* player);
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	bool playerIsDead = false;
	float player1Speed = 25.0f;
	float player2Speed = 25.0f;*/
};

