#include "Maths.h"
#include <random>

const float Maths:: pi = 3.14159265358979323846f;

float Maths::DegToRad(float deg)
{
	deg = deg * pi / 180.0f;
	return deg;
}

float Maths::RadToDeg(float rad)
{
	rad = rad * 180.0f / pi;
	return rad;
}

float Maths::Lerp(float a, float b, float t)
{
	 return a + (b - a) * t;
}

float Maths::Clamp(float value, float min, float max)
{
	const float t = value < min ? min : value;
	return t > max ? max : t;
}

int Maths::Clamp(int value, int min, int max)
{
	const float t = value < min ? min : value;
	return t > max ? max : t;
}

float Maths::Abs(float value)
{
	if(value < 0) return -value;
	else return value;
}

float Maths::Max(float value1, float value2)
{
    return value1 > value2 ? value1 : value2;
}

float Maths::Min(float value1, float value2)
{
	return value1 < value2 ? value1 : value2;
}

int Maths::RandomRange(int min, int max)
{
    //INFO: Generate a random range between min and max(inclusive)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

float Maths::RandomRange(float min, float max)
{
	//INFO: Generate a random range between min and max(inclusive)
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

string Maths::FloatToString(float value, int precision)
{
	return std::to_string(value);
}

int Maths::RoundToInt(float f)
{
    return static_cast<int>(std::round(f));
}

float Maths::PingPong(float time, float length)
{
	float t = fmod(time, length * 2);
	if (t > length) {
		t = length * 2 - t;
	}
	return t;
}

float Maths::MoveTowards(float current, float target, float maxDelta)
{
    if (current < target)
    {
        current += maxDelta;
        if (current > target)
        {
            current = target;
        }
    }
    else if (current > target)
    {
        current -= maxDelta;
        if (current < target)
        {
            current = target;
        }
    }
    return current;
}

int Maths::FloorToInt(float f)
{
	return static_cast<int>(std::floor(f));
}

float Maths::Atan2(float y, float x)
{
	return std::atan2(y, x);
}
