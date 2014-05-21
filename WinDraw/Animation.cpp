
#include "Timer.h"
#include "Bitmap.h"
#include "Animation.h"

bool Animation::UpdateAndCheckCompletion()
{
	float currentTime = timer.TimeFromStart(); 
	for(int i=currentFrame; i<frameCount; i++) 
	{
		if(frames[i].frameTime > currentTime) 
		{
			currentFrame=i; 
			complete = false; 
			return false; 
		}
	}
	currentFrame = frameCount-1; 
	complete = true; 
	return true; 
}

Animation::Animation(Bitmap* bmp, int frameWidth, int frameHeight, int* indices, int indicesCount, float frameTime): 
		bitmap(bmp), currentFrame(0), complete(false), looping(false)
{
	int bmw = bitmap->GetWidth(); 
	int fx = bmw / frameWidth; 
	frameCount = indicesCount; 
	frames = new Frame[indicesCount]; 
	float animationTime = frameTime; 
	for(int i=0; i<frameCount; i++) 
	{
		int xIndex = (indices[i] % fx); 
		int yIndex = (indices[i] / fx); 
		frames[i].x = xIndex * frameWidth; 
		frames[i].y = yIndex * frameHeight; 
		frames[i].w = frameWidth; 
		frames[i].h = frameHeight; 
		frames[i].frameTime = animationTime; 
		animationTime+=frameTime; 
	}
}
//Starts animation playback
void Animation::Start(bool loop)
{
	currentFrame = 0; 
	looping = loop; 
	complete = false; 
	timer.Reset(); 
}

// updates and draws an animation based on time at (x, y) onto the renderTarget. 
void Animation::Draw(Bitmap* renderTarget, int x, int y) 
{
	if(UpdateAndCheckCompletion() && looping) 
	{
		currentFrame = 0; 
		timer.Reset(); 
	}
	Frame* f = &frames[currentFrame]; 
	bitmap->DrawRectTo(renderTarget, x, y, f->x, f->y, f->w, f->h); 
}

void Animation::DrawRotated(Bitmap* renderTarget, int x, int y, int pivotx, int pivoty, float radAngle)
{
	if(UpdateAndCheckCompletion() && looping) 
	{
		currentFrame = 0; 
		timer.Reset(); 
	}
	Frame* f = &frames[currentFrame]; 
	bitmap->DrawRectRotatedTo(renderTarget, x, y, f->x, f->y, f->w, f->h, pivotx, pivoty, radAngle); 
}

//true if an animation is complete. 
bool Animation::IsComplete()
{
	return complete; 
}

Animation::~Animation()
{
	delete[] frames; 
}
