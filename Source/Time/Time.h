#pragma once

#include <chrono>

class Time
{
public:
	static void Tick();

	static inline const float DeltaTime() { return deltaTime * timeScale; }
	static inline const float ElapsedTime() { return elapsedTime; }

	static inline void SetTimeScale(float scale) { timeScale = scale; }
	static inline const float TimeScale() { return timeScale; }

private:
	static float deltaTime;
	static float timeScale;
	static float elapsedTime;

	static std::chrono::time_point<std::chrono::steady_clock> currentTime;
	static std::chrono::time_point<std::chrono::steady_clock> previousTime;
};

