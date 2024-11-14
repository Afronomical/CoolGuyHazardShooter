#pragma once


#include "../Components/Component.h"
#include "../AssetLoading/AssetHandler.h"

class Animator
{
private:
	float timeElapsed = SDL_GetTicks()/500;

	bool isLooping;


	int FRAME_WIDTH = 16;   // Width of each frame in the spritesheet
	int FRAME_HEIGHT = 16;  // Height of each frame in the spritesheet
	    
	

protected:

public:

	SDL_Renderer* rend;
	Animator(std::string filePath, const Vector2* position, int numberOfRows, int numberOfColumns, int totalNumberOfFrames, int frameWidth, int frameHeight , float timeSpentPerFrame);

	//PNG of all sprites
	Asset spriteSheet;
	
	//INFO: The cookie cutter that gets a single frame from a sprite sheet
	SDL_Rect srcRect;
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

	//		time spent on a frame before moving to the next
	float frameDuration;

	
	const Vector2* position;
	void Update();
	
	// Update the SourceRect (srcRect) to display the next frame of the animation
	void DrawCurrentFrame();
};

