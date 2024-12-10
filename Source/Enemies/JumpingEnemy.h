#pragma once

#include "..\Enemies\BaseEnemy.h"
#include "..\Physics\Rigidbody.h"

class JumpingEnemy : public BaseEnemy
{
public:
	JumpingEnemy();
	~JumpingEnemy() override;

	virtual void Update(float deltaTime) override;

protected:
	std::weak_ptr<Rigidbody> rb;
	void CheckMapCollisions();

private:
	float mass = 50.0f;
	float gravity = -7.5f;
	float jumpHeight = 2.0f;
	float timeBetweenJumps = 1.0f;
	float jumpTimer;
	float jumpCooldown;
};