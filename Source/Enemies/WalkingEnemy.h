#pragma once

#include "..\Enemies\BaseEnemy.h"

class WalkingEnemy : public BaseEnemy
{
public:
	WalkingEnemy();
	~WalkingEnemy() override;

	virtual void Update(float deltaTime) override;

protected:
	float moveSpeed = 10.0f;

	bool walkingLeft;

	void CheckMapCollisions();
};