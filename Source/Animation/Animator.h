#pragma once


#include "../Components/Component.h"


class Animator : public Component
{
private:
	float timeElapsed;

	bool isLooping;
protected:

public:

	Animator();

	int frames, currentFrame;
	float frameDuration;


	void Update();

	void GetCurrentTexture();
};

