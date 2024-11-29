#pragma once

#include "..\Enemies\BaseEnemy.h"

class JumpingEnemy : public BaseEnemy
{
public:
	JumpingEnemy();
	~JumpingEnemy() override;

	virtual void Update(float deltaTime) override;

protected:
	float jumpHeight = 10.0f;

	void CheckMapCollisions();
};