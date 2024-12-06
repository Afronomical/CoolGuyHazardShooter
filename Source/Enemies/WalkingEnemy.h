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

protected:
	float moveSpeed = 10.0f;

	bool walkingLeft;

	void CheckMapCollisions();
};