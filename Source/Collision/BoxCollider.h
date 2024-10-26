#pragma once

#include "Collider.h"

class BoxCollider : public Collider
{
public:
	/// @param useCustomFunctions : If false, the default collision functions held in GameObject will be used
	/// otherwise if true, you'll need to set the desired collision functions yourself 
	BoxCollider(GameObject* _gameObject, bool useCustomFunctions = false);
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

