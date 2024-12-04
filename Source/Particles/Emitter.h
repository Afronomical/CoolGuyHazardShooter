#pragma once
#include "../Components/Component.h"
#include "Particle.h"

#define MAX_PARTICLES 100

class Particle;

class Emitter : public Component
{
private:

	int radius;
	int particleCount;
	std::vector<Particle*> particles;//[MAX_PARTICLES];

public:

	Emitter(GameObject* go, float duration);
	//using Component::Component;

	/// <summary>
	/// Spawns, moves and removes a single particle
	/// To be used in a loop
	/// </summary>
	/// <param name="range"> How far each particle travels </param>
	/// <param name="size"> How big each particle is </param>
	/// <param name="texture"> What each particle looks like </param>
	/// <param name="position"> Origin point of particles </param>
	void EmitParticles(int range, float size, const Asset& texture, const Vector2& position);
};

