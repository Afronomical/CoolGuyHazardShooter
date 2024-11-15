#include "Emitter.h"

void Emitter::EmitParticles(int range, float duration, const Asset& texture, const Vector2& position)
{
	//Set range of particles
	radius = range;

	for (int i = 0; i < MAX_PARTICLES; ++i)
	{
		if (!particles[i]) //If empty
		{
			particles[i]->SetLifetime(duration);

			//Create particle
			particles[i] = new Particle(particles[i]->GetLifetime(), 2.0f, texture, position);

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

		else if (particles[i])//If not empty
		{
			if (particles[i]->GetLifetime() <= 0)//If out of time
			{
				//particles[i]->Destroy();
				//delete particles[i];
				//particles[i] = nullptr;//Double tap

				particles[i]->SetIsActive(false);
			}
			else if(!particles[i]->IsActive() && duration > 0)
			{
				particles[i]->SetPosition(position);
				particles[i]->SetLifetime(duration);
				particles[i]->SetIsActive(true);
			}
		}

		//Decrement the particle's lifetime
		particles[i]->SetLifetime(particles[i]->GetLifetime() - Time::DeltaTime());
	}
}