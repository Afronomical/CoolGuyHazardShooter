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

class Rigidbody : public Component
{
public:
	class Handler
	{
	public:
		/// @brief Sets the gravity value that will be used by all newly created Rigidbody components
		/// after this function is called
		inline static void SetGlobalGravity(float _gravity) { globalGravity = _gravity; }
		inline static float GetGlobalGravity() { return globalGravity; }

	private:
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
	
	/// @brief Called by the user to update the Rigidbody component based on the changes
	/// made previously through functions like AddForce
	/// @param deltaTime : The time between frames
	void Update(float deltaTime);

	void AddForce(const Vector2& _force, ForceMode mode = ForceMode::Force);
	inline void AddForce(float forceX, float forceY, ForceMode mode = ForceMode::Force) { AddForce(Vector2(forceX, forceY), mode); }

	inline void CancelForce() { force = Vector2::Zero; }
	inline void CancelForceX() { force.X = 0.0f; }
	inline void CancelForceY() { force.Y = 0.0f; }

	inline void SetMass(float _mass) { mass = _mass; }
	inline float GetMass() const { return mass; }

	/// @brief Sets the gravity value that will be used by this Rigidbody component
	inline void SetGravity(float _gravity) { gravity = _gravity; }
	inline float GetGravity() const { return gravity; }

	inline const Vector2& GetAcceleration() const { return acceleration; }

	inline void SetVelocity(const Vector2& _velocity) { velocity = _velocity; }
	inline const Vector2& GetVelocity() const { return velocity; }

	inline const Vector2& GetDisplacement() const { return displacement; }

private:
	static float dragCoefficient;
	float mass;
	float gravity;

	Vector2 force;
	Vector2 acceleration;
	Vector2 velocity;
	Vector2 displacement;
};

