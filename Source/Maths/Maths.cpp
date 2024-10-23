#include "Maths.h"

#include <cmath>
#include <ctime>
#include <iomanip>
#include <sstream>

const float Maths::PI = 3.1415f;

float Maths::DegToRad(float deg)
{
	return deg * (PI / 180.0f);
}

float Maths::RadToDeg(float rad)
{
	return rad * (180.0f / PI);
}

float Maths::Lerp(float a, float b, float t)
{
	t = Clamp(t, 0.0f, 1.0f);
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
	return std::abs(value);
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
    int range = max - min;
    return min + rand() % range;
}

float Maths::RandomRange(float min, float max)
{
	//INFO: Generate a random range between min and max(inclusive)
    float range = max - min;
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / range));
}

std::string Maths::FloatToString(float value, int precision)
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(precision) << value;
    return stream.str();
}

int Maths::RoundToInt(float f)
{
    return static_cast<int>(std::round(f));
}

float Maths::PingPong(float time, float length)
{
	float t = std::fmod(time, length * 2);
	if (t > length)
		t = length * 2 - t;

	return t;
}

float Maths::MoveTowards(float current, float target, float maxDelta)
{
    if (current < target)
    {
        current += maxDelta;

        if (current > target)
            current = target;
    }
    else if (current > target)
    {
        current -= maxDelta;

        if (current < target)
            current = target;
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
