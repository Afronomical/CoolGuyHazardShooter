#pragma once

#include "../Components/Component.h"

#include <functional>
#include <vector>

#include "../Vector2/Vector2.h"
#include "../Layers/TileLayer.h"

class BoxCollider;
class CircleCollider;

class Collider : public Component, public std::enable_shared_from_this<Collider>
{
public:
	class Handler
	{
	public:
		/// @brief Utility function used to check for collisions between all colliders
		static void CheckCollisions();

		/// @brief Utility function used to check for collisions between the given entity and the map
		/// @param position : The position of the entity
		/// @param width : The width of the entity
		/// @param height : The height of the entity
		/// @return Whether the entity has collided with the map
		static bool CheckMapCollision(const Vector2& position, float width, float height);

		static inline void SetMapCollisionLayer(TileLayer* collisionLLayer) { mapCollisionLayer = collisionLLayer; }

		/// @brief Used to register a collider with the handler
		/// @param collider : The collider to register
		static inline void RegisterCollider(std::shared_ptr<Collider> collider) { colliders.push_back(collider); }

		/// @brief Used to clear all expired colliders from the handler at the end of the frame
		static void ClearExpiredColliders();

	private:
		static void CircleCircleCollision(std::shared_ptr<CircleCollider> c1, std::shared_ptr<CircleCollider> c2);
		static void BoxBoxCollision(std::shared_ptr<BoxCollider> b1, std::shared_ptr<BoxCollider> b2);
		static void CircleBoxCollision(std::shared_ptr<CircleCollider> c, std::shared_ptr<BoxCollider> b);

		static void HandleCollisionResponse(std::shared_ptr<Collider> c1, std::shared_ptr<Collider> c2, bool hasCollided);

	private:
		static std::vector<std::weak_ptr<Collider>> colliders;
		static TileLayer* mapCollisionLayer;

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

	/// @brief Used by the user to update the collider's position using the GameObject's position
	/// also takes into account the offset that was set by the user
	/// @param _position : The position of the GameObject
	inline void UpdateCollider(const Vector2& _position) { position = _position + offset; }
	inline const Vector2& GetPosition() const { return position; }
	virtual Vector2 GetCentrePosition() const = 0;

	inline void SetOffset(const Vector2& _offset) { offset = _offset; }
	inline const Vector2& GetOffset() const { return offset; }

	/// @brief Whether the collider will perform trigger events or collision events
	inline void SetIsTrigger(bool _isTrigger) { isTrigger = _isTrigger; }
	inline bool IsTrigger() const { return isTrigger; }


	// INFO: Setters for custom collision functions, in case the user adds more than one collider to a GameObject

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

