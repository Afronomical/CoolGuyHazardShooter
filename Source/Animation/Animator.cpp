#include "Animator.h"



Animator::Animator(std::string filePath, const Vector2* position, int numberOfRows, int numberOfColumns, int totalNumberOfFrames, int frameWidth, int frameHeight, float timeSpentPerFrame)
{
	spriteSheet = AssetHandler::LoadTexture(filePath);
	
	this->position = position;
	this->numRows = numberOfRows;
	this->numCols = numberOfColumns;
	this->totalFrames = totalNumberOfFrames;
	this->FRAME_WIDTH = frameWidth;
	this->FRAME_HEIGHT = frameHeight;
	this->frameDuration = timeSpentPerFrame;


	currentFrame = 0;  
	timeElapsed = 0;   

	srcRect = { 0, 0, FRAME_WIDTH, FRAME_HEIGHT };
}

void Animator::Update()
{
	Uint32 currentTime = SDL_GetTicks();
	if (currentTime - timeElapsed >= frameDuration) {
		
		currentFrame = (currentFrame + 1) % totalFrames;
		timeElapsed = currentTime;
	}

	//Deprecated as is handled by AssetHandler::DrawAnimation()
	/*if (totalFrames > 0)
	{
		int currentFrameIndex = (int)(timeElapsed * frameDuration) % totalFrames;

		srcRect.x = currentFrame * FRAME_WIDTH;
		srcRect.y = animationRow * FRAME_HEIGHT;
		srcRect.w = FRAME_WIDTH;
		srcRect.h = FRAME_HEIGHT;
	}*/

}

void Animator::DrawCurrentFrame()
{
	AssetHandler::DrawAnimation(spriteSheet, *position, srcRect.w, srcRect.h, animationRow, currentFrame, 0, scale, flippedOnAxis);
	
}