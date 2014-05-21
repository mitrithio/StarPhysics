
#include "Timer.h"
#include "platform.h"

float Timer::now()
{
    return ::getHiResTime(frequency);
}

Timer::Timer()
{
	initHiResTimer(&frequency);
	Reset(); 
}

void Timer::Reset()
{
	float currentTime = now(); 
	startTime = currentTime; 
	lastTime = currentTime; 
}

float Timer::TimeFromStart()
{
	float currentTime = now(); 
	lastTime = currentTime;
	return currentTime - startTime; 
}

float Timer::TimeFromLast()
{
	float currentTime = now(); 
	float elapsed = currentTime- lastTime;
	lastTime = currentTime; 
	return elapsed; 
}
 
