#pragma once

#include <chrono>

class Time
{
public:
	/// @brief Used to update the time values
	static void Tick();

	/// @return The time between frames
	static inline const float DeltaTime() { return deltaTime * timeScale; }

	/// @return The total time since the game started
	static inline const float ElapsedTime() { return elapsedTime; }

	static inline void SetTimeScale(float scale) { timeScale = scale; }
	static inline const float TimeScale() { return timeScale; }

private:
	static float deltaTime;
	static float timeScale;
	static float elapsedTime;

	static std::chrono::time_point<std::chrono::steady_clock> currentTime;
	static std::chrono::time_point<std::chrono::steady_clock> previousTime;

private:
	Time() = delete;
	~Time() = delete;
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;
};

