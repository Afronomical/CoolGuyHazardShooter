#include "AnimatorController.h"




AnimatorController::AnimatorController(GameObject* gm) : Component(gm)
{
	
}

void AnimatorController::Initialize()
{
	
}

void AnimatorController::Update()
{
	if (currentAnimation != nullptr)
	{
		currentAnimation->Update();
	}

}

void AnimatorController::Draw()
{
	if (currentAnimation != nullptr)
	{
		currentAnimation->DrawCurrentFrame();
	}

}



bool AnimatorController::SetCurrentAnimation(const char* AnimationToPlay)
{
	if (ListOfAnimators[AnimationToPlay] == nullptr)
	{
		Debug::LogError("Error @ AnimatorController::SetCurrentAnimation,  No animation found with the name " + std::string(AnimationToPlay));
		return false;
	}
	else
	{
		currentAnimation = ListOfAnimators[AnimationToPlay];
		return true;
	}

}

bool AnimatorController::AddAnimation(const char* AnimationName, Animator* AnimationToPlay)
{

	if (ListOfAnimators[AnimationName] = nullptr)
	{
		ListOfAnimators[AnimationName] = AnimationToPlay;
		return true;
	}
	else
	{
		Debug::LogWarning("Error @ AnimatorController::AddAnimation,  there is already an animation bound to " + std::string(AnimationName));
		return false;
	}
}

bool AnimatorController::AddAnimation(const char* AnimationName, std::string filePath, const Vector2& position, int numberOfRows, int numberOfColumns, int totalNumberOfFrames, int frameWidth, int frameHeight, float timeSpentPerFrame)
{

	if (ListOfAnimators[AnimationName] == nullptr)
	{
		ListOfAnimators[AnimationName] = new Animator(filePath, position, numberOfRows, numberOfColumns, totalNumberOfFrames, frameWidth, frameHeight, timeSpentPerFrame);
		return true;
	}
	else
	{
		Debug::LogWarning("Error @ AnimatorController::AddAnimation,  there is already an animation bound to " + std::string(AnimationName));
		return false;
	}

}
