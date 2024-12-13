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
#include "../Player/Player.h"
class Missile : public GameObject
{
public:
	Missile(Player* player1Ref, Player* player2Ref);
	~Missile();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void MissileMove();

	float delta = 0;

	Vector2 target;
	Vector2 forward;
	Vector2 randRot;
	Vector2 startPos;
	Asset missileTexture;

	float turnSpeed = 1;
	float missileSpeed = 3;
	float accel = 0.3f;
	float distanceToPlayer1 = 0;
	float distanceToPlayer2 = 0;
	float distanceToDestroy = 20;
	float randDirDuration = 1;
	float randDirTime = 0;
	float randDirRange = 0.6f;
	Vector2 DirectionToPlayer(Player* playerObj);
	Vector2 moveAngle = 0;
	void RandDir();
	void MissileHit();

	float GetRotationInDegrees(const Vector2& normalizedVector);

private:
	Player* player1;
	Player* player2;

};

