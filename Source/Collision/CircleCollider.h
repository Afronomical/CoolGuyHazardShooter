#pragma once

#include "Collider.h"

class CircleCollider : public Collider
{
public:
	CircleCollider(GameObject* _gameObject);
	~CircleCollider() override {};

	inline Vector2 GetCentrePosition() const override { return Vector2(position.X + radius, position.Y + radius); }

	inline void SetRadius(float _radius) { radius = _radius; }
	inline float GetRadius() const { return radius; }

private:
	float radius;
};

