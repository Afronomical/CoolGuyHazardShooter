#pragma once

#include "../Components/Component.h"
#include "../AssetLoading/AssetHandler.h"
#include "../GameObject/GameObject.h"
#include "../Components/Transform.h"

class Particles : public Component
{
public:

	int radius;
	float lifeTime;

	Vector2 pos;

	AssetHandler particleManager;

	using Component::Component;
	~Particles() override {};

	void StartParticleSystem(int range, float duration, Asset texture);
};

