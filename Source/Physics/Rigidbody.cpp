#include "Rigidbody.h"

#include "../Time/Time.h"

#pragma region StaticHandlerMembers
std::vector<std::weak_ptr<Rigidbody>> Rigidbody::Handler::rigidbodies;
float Rigidbody::Handler::globalGravity = 9.81f;
#pragma endregion StaticHandlerMembers

#pragma region StaticRigidbodyMembers
float Rigidbody::dragCoefficient = 0.5f;
#pragma endregion StaticRigidbodyMembers

#pragma region HandlerMethods
void Rigidbody::Handler::Update(float deltaTime)
{
	// INFO: Loop through all rigidbodies and call their Update function
	for (auto& rigidbody : rigidbodies)
		rigidbody.lock()->Update(deltaTime);
}

void Rigidbody::Handler::UnregisterRigidbody(std::shared_ptr<Rigidbody> rigidbody)
{
	// INFO: Iterates over the rigidbodies ensuring the rigidbody is not nullptr before removing the rigidbody
	rigidbodies.erase(
		std::remove_if(
			rigidbodies.begin(),
			rigidbodies.end(),
			[&rigidbody](std::weak_ptr<Rigidbody> registeredRigidbody) {
				return !registeredRigidbody.expired() && registeredRigidbody.lock() == rigidbody;
			}
		),
		rigidbodies.end()
	);
}
#pragma endregion HandlerMethods

#pragma region RigidbodyMethods
Rigidbody::Rigidbody(GameObject* _gameObject) : Component(_gameObject), mass(1.0f), gravityDirection(Vector2::Down), acceleration(Vector2::Zero), 
												velocity(Vector2::Zero), displacement(Vector2::Zero)
{
	// INFO: Register the rigidbody with the handler
	Rigidbody::Handler::RegisterRigidbody(shared_from_this());

	// INFO: Set gravity to global gravity value
	gravity = Rigidbody::Handler::GetGlobalGravity();
}

void Rigidbody::AddForce(const Vector2& _force, ForceMode mode)
{
	float deltaTime = Time::DeltaTime();

	switch (mode)
	{
	case ForceMode::Force:
		force += _force * deltaTime / mass;
		break;
	case ForceMode::Acceleration:
		force += _force * deltaTime;
		break;
	case ForceMode::Impulse:
		force += _force / mass;
		break;
	case ForceMode::VelocityChange:
		force += _force;
		break;
	case ForceMode::None:
	default:
		break;
	}
}

void Rigidbody::Update(float deltaTime)
{
	// INFO: Calculate gravitational force based on mass as well as the
	//       force applied to the rigidbody
	Vector2 gravitationalForce = gravityDirection * gravity * mass;

	// INFO: Calculate drag force based on the velocity of the rigidbody
	Vector2 unitVelocity = velocity.Normalized();
	Vector2 dragForce = unitVelocity * (-dragCoefficient * velocity.Magnitude());

	// INFO: Include drag force in the total force applied to the rigidbody
	Vector2 totalForce = gravitationalForce + force + dragForce;

	// INFO: Calculate acceleration based on the total force applied to the rigidbody
	acceleration = totalForce / mass;

	// INFO: Calculate velocity based on the acceleration of the rigidbody
	velocity += acceleration * deltaTime;

	// INFO: Calculate terminal velocity
	Vector2 terminalVelocity = gravitationalForce * mass / dragCoefficient;

	// INFO: Prevent the rigidbody from exceeding terminal velocity
	if (velocity.Magnitude() > terminalVelocity.Magnitude())
	{
		// INFO: Normalize the velocity
		Vector2::Normalize(velocity);
		
		// INFO: Scale the velocity to the terminal velocity
		velocity *= terminalVelocity.Magnitude();
	}

	// INFO: Calculate displacement based on the velocity of the rigidbody
	displacement = velocity * deltaTime;
}
#pragma endregion RigidbodyMethods
