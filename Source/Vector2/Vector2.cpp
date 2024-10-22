#include "Vector2.h"

#include <cmath>

//#include "Maths.h"

const Vector2 Vector2::Up(0, 1);
const Vector2 Vector2::Down(0, -1);
const Vector2 Vector2::Left(-1, 0);
const Vector2 Vector2::Right(1, 0);
const Vector2 Vector2::Zero(0, 0);
const Vector2 Vector2::One(1, 1);

Vector2::Vector2(float _X, float _Y) : X(_X), Y(_Y)
{
}

const Vector2 Vector2::Normalized()
{
	Vector2 v = *this;
	Normalize(v);
	return v;
}

const float Vector2::Magnitude() const
{
	return std::sqrt(X * X + Y * Y);
}

const float Vector2::SqrMagnitude() const
{
	return X * X + Y * Y;
}

void Vector2::MoveTowards(const Vector2& target, float maxDistanceDelta)
{
	// INFO: Direction from the current vector to the target vector
	Vector2 direction = target - *this;

	float distance = direction.Magnitude();

	// INFO: If the distance is already smaller than the maxDistanceDelta, no need to move
	if (std::abs(distance) <= maxDistanceDelta)
	{
		*this = target;
	}
	else
	{
		Normalize(direction);

		// INFO: Move the current vector towards the target vector by maxDistanceDelta
		*this = *this + direction * maxDistanceDelta;
	}
}

void Vector2::Normalize(Vector2& vector)
{
	float magnitude = vector.Magnitude();
	if (magnitude > 0)
		vector /= magnitude;
}

float Vector2::Distance(const Vector2& a, const Vector2& b)
{
	Vector2 V = a - b;
	return V.Magnitude();
}

float Vector2::Dot(const Vector2& a, const Vector2& b)
{
	return a.X * b.X + a.Y * b.Y;
}

Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
{
	//t = Maths::Clamp(t, 0.0f, 1.0f);
	return a + (b - a) * t;
}

Vector2 Vector2::MoveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta)
{
	// INFO: Direction from the current vector to the target vector
	Vector2 direction = target - current;

	float distance = direction.Magnitude();

	// INFO: If the distance is already smaller than the maxDistanceDelta, no need to move
	if (std::abs(distance) <= maxDistanceDelta)
	{
		return target;
	}
	else
	{
		Normalize(direction);

		// INFO: Move the current vector towards the target vector by maxDistanceDelta
		return current + direction * maxDistanceDelta;
	}
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	X += other.X;
	Y += other.Y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	X -= other.X;
	Y -= other.Y;
	return *this;
}

Vector2& Vector2::operator*=(const Vector2& other)
{
	X *= other.X;
	Y *= other.Y;
	return *this;
}

Vector2& Vector2::operator*=(float nr)
{
	X *= nr;
	Y *= nr;
	return *this;
}

Vector2& Vector2::operator/=(const Vector2& other)
{
	X /= other.X;
	Y /= other.Y;
	return *this;
}

Vector2& Vector2::operator/=(float nr)
{
	X /= nr;
	Y /= nr;
	return *this;
}

Vector2& Vector2::operator=(const Vector2& other)
{
	// INFO: Self-Assignment Safe
	if (this != &other)
	{
		X = other.X;
		Y = other.Y;
	}

	return *this;
}
