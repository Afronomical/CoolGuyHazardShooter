#pragma once
#include "Animator.h"
#include "../Components/Component.h"
#include "../Debugging/Debug.h"




class AnimatorController : public Component
{
private:

	// Parameters: <Name of Anim, Animator Reference>
	std::unordered_map<const char*, Animator*> ListOfAnimators;

	//Currently played Animation
	Animator* currentAnimation;
public:
	//Call to Add AnimatorController to StaticHandler  {NOT YET COMPLETE}
	void Initialize();

	void Update(float deltaTime);
	void Draw();
	//Info: returns true if successfully changed the playing Animation
	bool SetCurrentAnimation(const char* AnimationToPlay);
	
	//Add a new animation from Animator pointer
	bool AddAnimation(const char* AnimationName, Animator* AnimationToPlay);
	
	//Add a new Animation from scratch
	bool AddAnimation(	const char* AnimationName,	std::string filePath,	const Vector2& position,
						int numberOfRows,			int numberOfColumns,	int totalNumberOfFrames,
						int frameWidth,				int frameHeight,		float timeSpentPerFrame);
};

