#include "Particle.h"

void Particle::StartParticleSystem(int range, float duration, const Asset& texture, const Vector2& position)
{
	lifeTime = duration;
	radius = range;

	if(lifeTime > 0)
	{
		AssetHandler::DrawDynamic(texture, position, 2.f, 2.f);

		float dirX = Maths::RandomRange(0.f, 1.f);
		float dirY = Maths::RandomRange(0.f, 1.f);

		Vector2 randomDir = { dirX, dirY };

		pos += randomDir;

		if (pos.X > position.X + radius || pos.Y > position.Y + radius)
		{
			//Disable single particle
		}
		
		lifeTime -= Time::DeltaTime();
	}
}
