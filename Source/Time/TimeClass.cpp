#include "TimeClass.h"
std::chrono::time_point<std::chrono::steady_clock> TimeClass::currentTime = std::chrono::steady_clock::now();
std::chrono::time_point<std::chrono::steady_clock> TimeClass::previousTime = std::chrono::steady_clock::now();
float TimeClass::deltaTime = 0;
float TimeClass::timeScale = 1;
float TimeClass::elapsedTime = 0;

void TimeClass::Tick()
{
	previousTime = currentTime;
	currentTime = std::chrono::steady_clock::now();

	std::chrono::duration<float> elapsedTime = currentTime - previousTime;
	deltaTime = elapsedTime.count() * timeScale;
	
}

const float TimeClass::DeltaTime()
{
	return deltaTime;
}

const float TimeClass::ElapsedTime()
{
	return elapsedTime;
}

void TimeClass::SetTimeScale(float scale)
{
	timeScale = scale;
}

const float TimeClass::TimeScale()
{
	return timeScale;
}

TimeClass::TimeClass()
{
	previousTime = std::chrono::steady_clock::now();
	currentTime = std::chrono::steady_clock::now();
}

TimeClass::~TimeClass()
{

}
