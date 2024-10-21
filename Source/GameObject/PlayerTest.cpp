#include "PlayerTest.h"

#include "../Components/Transform.h"

#include <iostream>

#include "../MemoryLeakDetector/MemoryLeakDetector.h"

PlayerTest::PlayerTest() : GameObject()
{
	otherTransform = GetComponent<Transform>();
	bool removed = RemoveComponent<Transform>(transform);

	if (transform == nullptr)
	{
		std::cout << "Hi\n";
	}

	otherTransform->Translate(1.0f, 1.0f);
	otherTransform->GetGameObject();

	if (otherTransform = nullptr)
	{
		std::cout << "Hello\n";
	}
}
