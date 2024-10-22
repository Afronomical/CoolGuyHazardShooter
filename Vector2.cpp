#include "Vector2.h"
#include "math.h"

Vector2::Vector2()
{
	X = 0;
	Y = 0;
}

Vector2::Vector2(float x, float y)
{
	X = x;
	Y = y;
}

const float Vector2::Magnitude()
{
	return sqrt(X * X + Y * Y);
}

const float Vector2::SqrMagnitude()
{
	return X * X + Y * Y;
}

const Vector2 Vector2::Normalized()
{
	double magnitude = sqrt(X * X + Y * Y);
	if (magnitude > 0)
	{
		X /= magnitude;
		Y /= magnitude;
	}
	return Vector2(X, Y);
}

Vector2 Vector2::Normalize(Vector2& vector)
{
	double magnitude = sqrt(vector.X * vector.X + vector.Y * vector.Y);
	if (magnitude > 0)
	{
		vector.X /= magnitude;
		vector.Y /= magnitude;
	}
	return vector;  //return the normalized vector
}

float Vector2::Distance(const Vector2& a, const Vector2& b)
{
	double deltaX = a.X - b.X;
	double deltaY = a.Y - b.Y;
	return sqrt(deltaX * deltaX + deltaY * deltaY);
}

float Vector2::Dot(const Vector2& a, const Vector2& b)
{
	return a.X * b.X + a.Y * b.Y;
}

Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
{
	double newX = a.X + t * (b.X - a.X);
	double newY = a.Y + t * (b.Y - a.Y);
	return Vector2(newX, newY);
}

Vector2 Vector2::MoveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta)
{
	//direction from the current vector to the target vector
	Vector2 direction = target - current;

	float distance = direction.Magnitude();

	//if the distance is already smaller than the maxDistanceDelta, no need to move
	if (distance == 0.f || distance <= maxDistanceDelta)
	{
		return target;
	}
	else
	{
		Normalize(direction);

		//move the current vector towards the target vector by maxDistanceDelta
		return current + direction * maxDistanceDelta;
	}
}

void Vector2::MoveTowards(const Vector2& target, float maxDistanceDelta)
{
	//direction from the current vector to the target vector
	Vector2 direction = target - *this;
	
	float distance = direction.Magnitude();

	//if the distance is already smaller than the maxDistanceDelta, no need to move
	if (distance == 0.f || distance <= maxDistanceDelta)
	{
		*this = target;
	}
	else
	{
		Normalize(direction);

		//move the current vector towards the target vector by maxDistanceDelta
		*this = *this + direction * maxDistanceDelta;
	}
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(X + other.X, Y + other.Y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(X - other.X, Y - other.Y);
}

bool Vector2::operator==(const Vector2& other) const
{
	return (X == other.X && Y == other.Y);
}

bool Vector2::operator!=(const Vector2& other) const
{
	return !(*this == other);
}

Vector2 Vector2::operator*(float nr) const
{
	return Vector2(X * nr, Y * nr);
}

Vector2 Vector2::operator/(float nr) const
{
	return Vector2(X / nr, Y / nr);
}
