#pragma once

class Layer
{
public:
	virtual ~Layer() = default;

	virtual void Draw() = 0;
};

