#pragma once

#include "Collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider(GameObject* _gameObject);
	~BoxCollider() override {};

	inline Vector2 GetCentrePosition() const override { return Vector2(position.X + width / 2.0f, position.Y + height / 2.0f); }

	inline void SetWidth(float _width) { width = _width; }
	inline float GetWidth() const { return width; }

	inline void SetHeight(float _height) { height = _height; }
	inline float GetHeight() const { return height; }

private:
	float width;
	float height;
};

