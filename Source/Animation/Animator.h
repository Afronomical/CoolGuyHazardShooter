#pragma once


#include "../Components/Component.h"
#include "../AssetLoading/AssetHandler.h"
#include "../Time/Time.h"

class Animator
{
private:
	float timeElapsed = Time::ElapsedTime()/500;

	int frameWidth = 16;  
	int frameHeight = 16;  
	//Info: PNG of all sprites
	Asset spriteSheet;

	//Info: number of rows for each animation aka each new animation on the sheet
	int numRows;
	//Info: number of columns per animation aka each frame of a single animation
	int numCols;

	float scale = 1.0f;

	//Info: if not flipped SDL_FLIP_NONE otherwize use SDL_FLIP_VERTICAL or SDL_FLIP_HORIZONTAL
	SDL_RendererFlip flippedOnAxis;
	//Info: the row that line of the spritesheet the animator will play from
	int animationRow = 0;
	// {Number of frames on a row}			{the currently visual frame}
		int totalFrames,						currentFrame = 0;

	//Info: time spent on a frame before moving to the next
	float frameDuration;
protected:

public:


	void SetAnimatorValues(	std::string filePath, 
							const Vector2& position, 
							int numberOfRows, int numberOfColumns, 
							int totalNumberOfFrames, 
							int frameWidth, int frameHeight, 
							float timeSpentPerFrame);
	
	Vector2& position;
	
	// Info: Update the SourceRect (srcRect) to display the next frame of the animation
	void Update();
	//Info: Call the draw function
	void DrawCurrentFrame() const;

	
};

