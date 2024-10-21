#pragma once
#include "GameObject.h"
class PlayerTest : public GameObject
{
public:
	Transform* otherTransform;
	//using GameObject::GameObject;
	PlayerTest();

	~PlayerTest() override {};
};

