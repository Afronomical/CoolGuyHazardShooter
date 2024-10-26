#pragma once

#include "Collider.h"

class CircleCollider : public Collider
{
public:
	/// @param useCustomFunctions : If false, the default collision functions held in GameObject will be used
	/// otherwise if true, you'll need to set the desired collision functions yourself 
	CircleCollider(GameObject* _gameObject, bool useCustomFunctions = false);
	~CircleCollider() override {};

	inline Vector2 GetCentrePosition() const override { return Vector2(position.X + radius, position.Y + radius); }

	inline void SetRadius(float _radius) { radius = _radius; }
	inline float GetRadius() const { return radius; }

private:
	float radius;
};

