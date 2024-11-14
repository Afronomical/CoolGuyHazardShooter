#pragma once
#include "Animator.h"
#include "../Components/Component.h"




class AnimatorController : public Component
{
private:

public:
	Animator* animComp;

	int stateMachine;

	
	
	void Update(float deltaTime);

	void DrawTexture();

};

