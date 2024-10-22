#include "PlayerTest.h"

#include "../Components/Transform.h"

#include <iostream>

#include "../MemoryLeakDetector/MemoryLeakDetector.h"

PlayerTest::PlayerTest() : GameObject()
{
	otherTransform = GetComponent<Transform>();
	bool removed = RemoveComponent<Transform>(transform.lock()->GetComponentID());

	if (transform.expired())
	{
		std::cout << "transform has expired\n";
	}

	if (otherTransform.expired())
	{
		std::cout << "other transform has expired\n";
	}
}
