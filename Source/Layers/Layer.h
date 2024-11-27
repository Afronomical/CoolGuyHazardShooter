#pragma once
#include "../Vector2/Vector2.h"

class Layer
{
public:
	virtual ~Layer() = default;

	virtual void Draw(const Vector2& position) = 0;
};

