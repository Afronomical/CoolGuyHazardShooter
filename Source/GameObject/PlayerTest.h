#pragma once
#include "GameObject.h"
class PlayerTest : public GameObject
{
public:
	std::weak_ptr<Transform> otherTransform;
	//using GameObject::GameObject;
	PlayerTest();

	~PlayerTest() override {};
};

