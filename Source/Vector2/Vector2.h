#pragma once

class Vector2
{
public:
	Vector2(float _X = 0.0f, float _Y = 0.0f);

	/// @return A new normalized vector of the vector that called the function
	const Vector2 Normalized();

	const float Magnitude() const;
	const float SqrMagnitude() const;
	void MoveTowards(const Vector2& target, float maxDistanceDelta);

	/// @brief Normalizes the original passed in vector
	static void Normalize(Vector2& vector);

	static float Distance(const Vector2& a, const Vector2& b);
	static float Dot(const Vector2& a, const Vector2& b);
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
	static Vector2 MoveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta);

	inline Vector2 operator+(const Vector2& other) const { return Vector2(X + other.X, Y + other.Y); }
	inline Vector2 operator-(const Vector2& other) const { return Vector2(X - other.X, Y - other.Y); }

	inline Vector2 operator*(const Vector2& other) const { return Vector2(X * other.X, Y * other.Y); }
	inline Vector2 operator*(float nr) const { return Vector2(X * nr, Y * nr); }

	inline Vector2 operator/(const Vector2& other) const { return Vector2(X / other.X, Y / other.Y); }
	inline Vector2 operator/(float nr) const { return Vector2(X / nr, Y / nr); }

	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);

	Vector2& operator*=(const Vector2& other);
	Vector2& operator*=(float nr);

	Vector2& operator/=(const Vector2& other);
	Vector2& operator/=(float nr);

	Vector2& operator=(const Vector2& other);

	inline bool operator==(const Vector2& other) const { return X == other.X && Y == other.Y; }
	inline bool operator!=(const Vector2& other) const { return X != other.X || Y != other.Y; }

public:
	float X;
	float Y;

	static const Vector2 Up;
	static const Vector2 Down;
	static const Vector2 Left;
	static const Vector2 Right;
	static const Vector2 Zero;
	static const Vector2 One;
};

