#ifndef ANIMATION_H
#define ANIMATION_H

#include "Timer.h"
#include "Bitmap.h"

class Animation
{
protected: 
	Timer timer; 
	Bitmap* bitmap; 
	struct Frame
	{
		int x; 
		int y; 
		int w; 
		int h; 
		float frameTime; 
	}; 
	Frame* frames; 
	int frameCount;

	int currentFrame; 
	bool complete; 
	bool looping; 

	bool UpdateAndCheckCompletion(); 
	Animation(const Animation&) {/*animations cannot be copied*/}
public: 
	//constructor
	Animation(Bitmap* bmp, int frameWidth, int frameHeight, int* indices, int indicesCount, float frameTime); 
	~Animation(); 
	
	void Start(bool loop = false);  //Starts animation playback
	void Draw(Bitmap* renderTarget, int x, int y); // updates and draws an animation based on time at (x, y) onto the renderTarget. 
	void DrawRotated(Bitmap* renderTarget, int x, int y, int pivotx, int pivoty, float radAngle); // updates and draws an animation at (x, y) with pivot at (pivotx, pivoty) based on time onto the renderTarget, rotating it by radAngle radians. 
	bool IsComplete(); //true if an animation is complete. 
	int GetWidth(){ return frames[0].w; }
	int GetHeight(){ return frames[0].h; }
}; 

#endif ANIMATION_H