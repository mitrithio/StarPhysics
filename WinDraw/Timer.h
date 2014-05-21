#ifndef WINDRAW_TIMER_H
#define WINDRAW_TIMER_H

class Timer
{
protected: 
	double frequency; 
	float startTime; 
	float lastTime; 

	float now(); 
public: 
	Timer();				//creates a timer. 
	void Reset();			//resets a timer. 
	float TimeFromStart();  //returns time since creation
	float TimeFromLast();	//returns time since creation, Reset(), TimeFromStart() or TimeFromLast(), whatever happened latest. 
}; 

#endif