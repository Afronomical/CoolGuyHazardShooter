#pragma once
#include "..\Animation\AnimatorController.h"
#include "..\Enemies\BaseEnemy.h"

class WalkingEnemy : public BaseEnemy
{
public:
	WalkingEnemy();
	~WalkingEnemy() override;

	virtual void Update(float deltaTime) override;
	virtual void Start() override;

	inline void SetWalkingLeft(bool left) { walkingLeft = left; }
	void TurnAround();

protected:
	float moveSpeed = 20.0f;

	bool walkingLeft;

	void CheckMapCollisions();
};