#pragma once

#include "../Components/Component.h"

#include <vector>
#include <functional>

#include "../Vector2/Vector2.h"

class Collider : public Component
{
protected:
	enum class Type
	{
		None,

		Box,
		Circle
	};

public:
	using Component::Component;

	inline void SetPosition(const Vector2& _position) { position = _position; }
	inline const Vector2& GetPosition() const { return position; }
	virtual const Vector2& GetCentrePosition() const = 0;

	inline void SetOffset(const Vector2& _offset) { offset = _offset; }
	inline const Vector2& GetOffset() const { return offset; }

	inline void SetIsTrigger(bool _isTrigger) { isTrigger = _isTrigger; }
	inline bool IsTrigger() const { return isTrigger; }

private:
	inline Collider::Type GetColliderType() const { return colliderType; }

	inline void AddCollidingCollider(Collider* collider) { collidingColliders.push_back(collider); }
	void RemoveCollidingCollider(Collider* collider);
	bool ContainsCollidingCollider(Collider* collider) const;

protected:
	Collider::Type colliderType;
	Vector2 position;
	Vector2 offset;

private:
	bool isTrigger;
	std::vector<Collider*> collidingColliders;

	std::function<void(Collider*)> OnCollisionEnter;
	std::function<void(Collider*)> OnCollisionStay;
	std::function<void(Collider*)> OnCollisionExit;

	std::function<void(Collider*)> OnTriggerEnter;
	std::function<void(Collider*)> OnTriggerStay;
	std::function<void(Collider*)> OnTriggerExit;
};

