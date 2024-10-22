#pragma once

#include "Component.h"

//#include "../Vector2/Vector2.h"

class Transform : public Component
{
public:
	using Component::Component;
	~Transform() override {};

	void Translate(const float x, const float y);
	//void Translate(const Vector2& translation);

public:
	//Vector2 position;
};
