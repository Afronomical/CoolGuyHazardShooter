#include "Time.h"

using namespace std::chrono;

float Time::deltaTime = 0.0f;
float Time::elapsedTime = 0.0f;
float Time::timeScale = 1.0f;

time_point<steady_clock> Time::currentTime = steady_clock::now();
time_point<steady_clock> Time::previousTime = steady_clock::now();

void Time::Tick()
{
	currentTime = std::chrono::steady_clock::now();

	// INFO: Time between frames
	deltaTime = static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - previousTime).count() / 1e9);

	// INFO: Time since the start of the application
	elapsedTime += deltaTime;
	
	previousTime = currentTime;
}
