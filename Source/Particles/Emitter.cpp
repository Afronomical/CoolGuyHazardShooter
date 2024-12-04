#include "Emitter.h"

Emitter::Emitter(GameObject* go, float duration) : Component(go), radius(5), particleCount(10)
{
	for (int i = 0; i < particleCount; ++i)
	{
		if (particles.size() < particleCount) //If empty
		{
			//Create particle
			Particle* particleTemp = new Particle(duration);//duration, 2.0f, texture, position);
			particles.push_back(particleTemp);

			//particles[i]->SetLifetime(duration);
		}
	}
}

void Emitter::EmitParticles(int range, float size, const Asset& texture, const Vector2& position)
{
	//Set range of particles
	radius = range;

	//TODO - Debug why it doesnt show on screen
	//for (int i = 0; i < MAX_PARTICLES; ++i)
	//{
	//	if (particles.size() < particleCount) //If empty
	//	{
	//		//Create particle
	//		Particle* particleTemp = new Particle(duration, 2.0f, texture, position);
	//		particles.push_back(particleTemp);

	//		particles[i]->SetLifetime(duration);

	//		//Create random direction
	//		float dirX = Maths::RandomRange(0.f, 1.f);
	//		float dirY = Maths::RandomRange(0.f, 1.f);

	//		Vector2 randomDir = { dirX, dirY };

	//		//Move particle in said direction
	//		particles[i]->SetPosition(randomDir * Time::DeltaTime());

	//		if (particles[i]->GetPosition().X > position.X + radius || particles[i]->GetPosition().Y > position.Y + radius)
	//		{
	//			//Remove the particle when out of range
	//			//particles[i]->Destroy();
	//			//delete particles[i];

	//			//Hide particle - particle pooling
	//			particles[i]->SetIsActive(false);
	//		}
	//	}
	//}

	if (particles.size() >= particleCount)//If not empty
	{
		for (auto& particle : particles)
		{
			if (particle->GetLifetime() > 0)
			{
				//Create random direction
				float dirX = Maths::RandomRange(0.f, 1.f);
				float dirY = Maths::RandomRange(0.f, 1.f);

				Vector2 randomDir = { dirX, dirY };

				//Move particle in said direction
				particle->SetPosition((position + randomDir) * Time::DeltaTime());

				if (particle->GetPosition().X > position.X + radius || particle->GetPosition().Y > position.Y + radius)
				{
					//Remove the particle when out of range
					//particles[i]->Destroy();
					//delete particles[i];

					//Hide particle - particle pooling
					particle->SetIsActive(false);
				}

				particle->Draw(texture, particle->GetPosition(), size);
			}
			else if (particle->GetLifetime() <= 0)//If out of time
			{
				//particles[i]->Destroy();
				//delete particles[i];
				//particles[i] = nullptr;//Double tap

				particle->SetIsActive(false);
			}
			else if (!particle->IsActive() && particle->GetLifetime() > 0)
			{
				particle->SetPosition(position);
				particle->SetLifetime(particle->GetLifetime());
				particle->SetIsActive(true);
			}

			//Decrement the particle's lifetime
			particle->SetLifetime(particle->GetLifetime() - Time::DeltaTime());
		}
	}

}