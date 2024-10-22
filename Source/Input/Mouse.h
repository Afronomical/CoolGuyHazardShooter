#pragma once

//#include "../Vector2/Vector2.h"

struct Mouse
{
	Mouse() : /*position(Vector2()),*/ width(0), height(0) {};
	inline void SetMouseData(/*const Vector2& _position,*/ float _width, float _height) 
	{ 
		/*position = _position;*/ 
		width = _width; 
		height = height; 
	}
	
	//Vector2 position;
	float width;
	float height;
};