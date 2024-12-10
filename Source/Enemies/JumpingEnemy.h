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
	float mass = 5000.0f;
	float gravity = -7.5f;
	float timeBetweenJumps = 10.0f;  // How long they will wait until they jump again
	float jumpTimer;  // How long they have been jumping for
	float jumpCooldown;  // Time till the next jump starts
	float jumpTime = 6;  // How long they will spend jumping
};