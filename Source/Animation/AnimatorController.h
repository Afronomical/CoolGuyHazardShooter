#pragma once
#include "Animator.h"




class AnimatorController
{
private:

public:
	Animator* animComp;

	int stateMachine;


	void Update();

	void DrawTexture();

};

