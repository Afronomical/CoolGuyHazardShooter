#pragma once
#include <chrono>
class TimeClass
{

private:
	static float deltaTime;

	static float timeScale;

	static float elapsedTime;

	static std::chrono::time_point<std::chrono::steady_clock> currentTime;

	static std::chrono::time_point<std::chrono::steady_clock> previousTime;

public: 
	static void Tick();

	static const float DeltaTime();

	static const float ElapsedTime();

	static void SetTimeScale(float scale);

	static const float TimeScale();

	TimeClass(); 

	~TimeClass();

};

