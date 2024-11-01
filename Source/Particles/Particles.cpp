#include "Particles.h"

void Particles::StartParticleSystem(int range, float duration, Asset texture)
{
	lifeTime = duration;
	radius = range;

	auto spawnLoc = this->GetGameObject()->GetComponent<Transform>().lock()->position;

	while (lifeTime > 0)
	{
		particleManager.DrawDynamic(texture, spawnLoc, 2.f, 2.f);

		Vector2 randomDir = { rand(), rand() };

		pos += randomDir;

		if (pos.X > spawnLoc.X + radius || pos.Y > spawnLoc.Y + radius)
		{
			//particleManager.Clean();
			//Disable single particle
		}
		
		--lifeTime;
	}
}
