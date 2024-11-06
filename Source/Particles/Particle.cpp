#include "Particle.h"

//void Particle::StartParticleSystem(int range, float duration, int particleCount, const Asset& texture, const Vector2& position)
//{
//	pLifeTime = duration;
//	radius = range;
//	maxParticles = particleCount;
//
//	if(lifeTime > 0)
//	{
//		for (int i = 0; i < maxParticles; ++i)
//		{
//			AssetHandler::DrawDynamic(texture, position, 2.f, 2.f);
//
//			float dirX = Maths::RandomRange(0.f, 1.f);
//			float dirY = Maths::RandomRange(0.f, 1.f);
//
//			Vector2 randomDir = { dirX, dirY };
//
//			pos += randomDir * Time::DeltaTime();
//
//			if (pos.X > position.X + radius || pos.Y > position.Y + radius)
//			{
//				//Disable single particle
//			}
//		}
//		
//		lifeTime -= Time::DeltaTime();
//	}
//}

Particle::Particle(float lifeTime, float size, const Asset& texture, const Vector2& position)
{
	AssetHandler::DrawDynamic(texture, position, size, size);
	SetLifetime(lifeTime);

}
