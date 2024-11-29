#include "Emitter.h"

void Emitter::EmitParticles(int range, float duration, int particleCount, const Asset& texture, const Vector2& position)
{
	//Set range of particles
	radius = range;

	//TODO - Debug why it doesnt show on screen
	for (int i = 0; i < MAX_PARTICLES; ++i)
	{
		if (particles.size() < particleCount) //If empty
		{
			//Create particle
			Particle* particleTemp = new Particle(duration, 2.0f, texture, position);
			particles.push_back(particleTemp);

			particles[i]->SetLifetime(duration);

			//Create random direction
			float dirX = Maths::RandomRange(0.f, 1.f);
			float dirY = Maths::RandomRange(0.f, 1.f);

			Vector2 randomDir = { dirX, dirY };

			//Move particle in said direction
			particles[i]->SetPosition(randomDir * Time::DeltaTime());


			if (particles[i]->GetPosition().X > position.X + radius || particles[i]->GetPosition().Y > position.Y + radius)
			{
				//Remove the particle when out of range
				//particles[i]->Destroy();
				//delete particles[i];

				//Hide particle - particle pooling
				particles[i]->SetIsActive(false);
			}
		}
	}

	if (particles.size() >= particleCount)//If not empty
	{
		for (auto& particle : particles)
		{
			if (particle->GetLifetime() <= 0)//If out of time
			{
				//particles[i]->Destroy();
				//delete particles[i];
				//particles[i] = nullptr;//Double tap

				particle->SetIsActive(false);
			}
			else if (!particle->IsActive() && duration > 0)
			{
				particle->SetPosition(position);
				particle->SetLifetime(duration);
				particle->SetIsActive(true);
			}

			//Decrement the particle's lifetime
			particle->SetLifetime(particle->GetLifetime() - Time::DeltaTime());
		}
	}

}