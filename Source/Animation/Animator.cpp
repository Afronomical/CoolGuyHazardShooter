#include "Animator.h"





void Animator::SetAnimatorValues(std::string filePath, const Vector2& position, int numberOfRows, int numberOfColumns, int totalNumberOfFrames, int frameWidth, int frameHeight, float timeSpentPerFrame)
{
	spriteSheet = AssetHandler::LoadTexture(filePath);

	this->position = position;
	this->numRows = numberOfRows;
	this->numCols = numberOfColumns;
	this->totalFrames = totalNumberOfFrames;
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
	this->frameDuration = timeSpentPerFrame;


	currentFrame = 0;
	timeElapsed = 0;

}

void Animator::Update()
{
	if (Time::DeltaTime() - Time::ElapsedTime() >= frameDuration) 
	{
		currentFrame = (currentFrame + 1) % totalFrames;
	}
}

void Animator::DrawCurrentFrame()
{
	AssetHandler::DrawAnimation(spriteSheet, position, frameWidth, frameHeight, animationRow, currentFrame, 0, scale, flippedOnAxis);
}