#pragma once

#include <string>

class Maths
{
public:
	static float DegToRad(float deg);
	static float RadToDeg(float rad);

	static float Lerp(float a, float b, float t);
	static float Clamp(float value, float min, float max);
	static int Clamp(int value, int min, int max);

	static float Abs(float value);
	static float Max(float value1, float value2);
	static float Min(float value1, float value2);

	static int RandomRange(int min, int max);
	static float RandomRange(float min, float max);

	static std::string FloatToString(float value, int precision);
	static int RoundToInt(float f);

	static float PingPong(float time, float length);
	static float MoveTowards(float current, float target, float maxDelta);
	static int FloorToInt(float f);
	static float Atan2(float y, float x);

public:
	static const float PI;
};

