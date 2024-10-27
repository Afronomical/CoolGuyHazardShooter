#pragma once

#include "../Components/Component.h"

#include <vector>

#include "../Vector2/Vector2.h"

enum class ForceMode
{
	None = 0,

	Force,
	Acceleration,
	Impulse,
	VelocityChange
};

class Rigidbody : public Component, public std::enable_shared_from_this<Rigidbody>
{
public:
	class Handler
	{
	public:
		static void Update(float deltaTime);

		inline static void SetGlobalGravity(float _gravity) { globalGravity = _gravity; }
		inline static float GetGlobalGravity() { return globalGravity; }

		inline static void RegisterRigidbody(std::shared_ptr<Rigidbody> rigidbody) { rigidbodies.push_back(rigidbody); }
		static void UnregisterRigidbody(std::shared_ptr<Rigidbody> rigidbody);

	private:
		static std::vector<std::weak_ptr<Rigidbody>> rigidbodies;
		static float globalGravity;

	private:
		Handler() = delete;
		~Handler() = delete;
		Handler(const Handler&) = delete;
		Handler& operator=(const Handler&) = delete;
	};

public:
	Rigidbody(GameObject* _gameObject);
	~Rigidbody() override {};

	void AddForce(const Vector2& _force, ForceMode mode = ForceMode::Force);
	inline void AddForce(float forceX, float forceY, ForceMode mode = ForceMode::Force) { AddForce(Vector2(forceX, forceY), mode); }

	inline void SetMass(float _mass) { mass = _mass; }
	inline float GetMass() const { return mass; }

	inline void SetGravity(float _gravity) { gravity = _gravity; }
	inline float GetGravity() const { return gravity; }

	inline void SetAcceleration(const Vector2& _acceleration) { acceleration = _acceleration; }
	inline const Vector2& GetAcceleration() const { return acceleration; }

	inline void SetVelocity(const Vector2& _velocity) { velocity = _velocity; }
	inline const Vector2& GetVelocity() const { return velocity; }

	inline const Vector2& GetDisplacement() const { return displacement; }

private:
	void Update(float deltaTime);

private:
	static float dragCoefficient;
	float mass;
	float gravity;

	Vector2 gravityDirection;
	Vector2 force;
	Vector2 acceleration;
	Vector2 velocity;
	Vector2 displacement;
};

