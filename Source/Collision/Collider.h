#pragma once

#include "../Components/Component.h"

#include <vector>
#include <functional>

#include "../Vector2/Vector2.h"

class BoxCollider;
class CircleCollider;

class Collider : public Component, public std::enable_shared_from_this<Collider>
{
public:
	class Handler
	{
	public:
		static void CheckCollisions();

		static void CircleCircleCollision(std::shared_ptr<CircleCollider> c1, std::shared_ptr<CircleCollider> c2);
		static void BoxBoxCollision(std::shared_ptr<BoxCollider> b1, std::shared_ptr<BoxCollider> b2);
		static void CircleBoxCollision(std::shared_ptr<CircleCollider> c, std::shared_ptr<BoxCollider> b);

		static void HandleCollisionResponse(std::shared_ptr<Collider> c1, std::shared_ptr<Collider> c2, bool hasCollided);

		inline static void RegisterCollider(std::shared_ptr<Collider> collider) { colliders.push_back(collider); }
		static void UnregisterCollider(std::shared_ptr<Collider> collider);

	private:
		static std::vector<std::weak_ptr<Collider>> colliders;

	private:
		Handler() = delete;
		~Handler() = delete;
		Handler(const Handler&) = delete;
		Handler& operator=(const Handler&) = delete;
	};

protected:
	enum class Type
	{
		None = 0,

		Box,
		Circle
	};

public:
	/// @param useCustomFunctions : If false, the default collision functions held in GameObject will be used
	/// otherwise if true, you'll need to set the desired collision functions yourself 
	Collider(GameObject* _gameObject, bool useCustomFunctions = false);

	inline void UpdateCollider(const Vector2& _position) { position = _position + offset; }
	inline const Vector2& GetPosition() const { return position; }
	virtual Vector2 GetCentrePosition() const = 0;

	inline void SetOffset(const Vector2& _offset) { offset = _offset; }
	inline const Vector2& GetOffset() const { return offset; }

	inline void SetIsTrigger(bool _isTrigger) { isTrigger = _isTrigger; }
	inline bool IsTrigger() const { return isTrigger; }

	inline void SetOnCollisionEnter(std::function<void(std::shared_ptr<Collider>)> function) { OnCollisionEnter = function; }
	inline void SetOnCollisionStay(std::function<void(std::shared_ptr<Collider>)> function) { OnCollisionStay = function; }
	inline void SetOnCollisionExit(std::function<void(std::shared_ptr<Collider>)> function) { OnCollisionExit = function; }

	inline void SetOnTriggerEnter(std::function<void(std::shared_ptr<Collider>)> function) { OnTriggerEnter = function; }
	inline void SetOnTriggerStay(std::function<void(std::shared_ptr<Collider>)> function) { OnTriggerStay = function; }
	inline void SetOnTriggerExit(std::function<void(std::shared_ptr<Collider>)> function) { OnTriggerExit = function; }

private:
	inline Collider::Type GetColliderType() const { return colliderType; }

	inline void AddCollidingCollider(std::shared_ptr<Collider> collider) { collidingColliders.push_back(collider); }
	void RemoveCollidingCollider(std::shared_ptr<Collider> collider);
	bool ContainsCollidingCollider(std::shared_ptr<Collider> collider) const;

protected:
	Collider::Type colliderType;
	Vector2 position;
	Vector2 offset;

private:
	bool isTrigger;
	std::vector<std::weak_ptr<Collider>> collidingColliders;

	std::function<void(std::shared_ptr<Collider>)> OnCollisionEnter;
	std::function<void(std::shared_ptr<Collider>)> OnCollisionStay;
	std::function<void(std::shared_ptr<Collider>)> OnCollisionExit;

	std::function<void(std::shared_ptr<Collider>)> OnTriggerEnter;
	std::function<void(std::shared_ptr<Collider>)> OnTriggerStay;
	std::function<void(std::shared_ptr<Collider>)> OnTriggerExit;
};
