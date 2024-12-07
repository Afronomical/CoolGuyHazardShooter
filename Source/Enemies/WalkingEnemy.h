#pragma once

#include "..\Enemies\BaseEnemy.h"

class WalkingEnemy : public BaseEnemy
{
public:
	WalkingEnemy();
	~WalkingEnemy() override;

	virtual void Update(float deltaTime) override;

	inline void SetWalkingLeft(bool left) { walkingLeft = left; }

protected:
	float moveSpeed = 20.0f;

	bool walkingLeft;

	void CheckMapCollisions();
};