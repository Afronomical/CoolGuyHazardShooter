#pragma once

#include "../Components/Component.h"
#include "../AssetLoading/AssetHandler.h"
#include "../Maths/Maths.h"
#include "../Time/Time.h"
#include "../GameObject/GameObject.h"
#include "../Components/Transform.h"

class Particle : public Component
{
private:

	int radius;
	float lifeTime;

	Vector2 pos;

public:

	using Component::Component;
	~Particle() override {};

	/// <summary>
	/// Spawns, moves and removes a single particle
	/// To be used in a loop
	/// </summary>
	/// <param name="range"> How far each particle travels </param>
	/// <param name="duration"> Duration of the entire particle effect </param>
	/// <param name="texture"> What each particle looks like </param>
	/// <param name="position"> Origin point of particles </param>
	void StartParticleSystem(int range, float duration, const Asset& texture, const Vector2& position);
};

