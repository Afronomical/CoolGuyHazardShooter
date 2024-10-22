#pragma once
class Vector2
{
public:
	float X;
	float Y;

	static const Vector2 Up;
	static const Vector2 Down;
	static const Vector2 Left;
	static const Vector2 Right;

	Vector2();
	Vector2(float x, float y);

	const float Magnitude();
	const float SqrMagnitude();
	const Vector2 Normalized();

	static Vector2 Normalize(Vector2& vector);
	static float Distance(const Vector2& a, const Vector2& b);
	static float Dot(const Vector2& a, const Vector2& b);
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
	static Vector2 MoveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta);

	void MoveTowards(const Vector2& target, float maxDistanceDelta);

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;
	Vector2 operator*(float nr) const;
	Vector2 operator/(float nr) const;


};

