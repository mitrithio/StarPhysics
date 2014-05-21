#ifndef WINDRAW_EVENT_HANDLER_H
#define WINDRAW_EVENT_HANDLER_H

#include "Bitmap.h"

enum KeyStatus
{
	KeyIdle = 0, 
	KeyPressed, 
	KeyReleased, 
	MouseMove, //mouse only
}; 

enum MouseKey
{
	No_Key,
	LMouse, 
	RMouse, 
}; 

class EventHandler
{
public: 
	virtual void OnInput(unsigned int Key, KeyStatus status) = 0; 
	virtual void OnMouseInput(int MousePosX, int MousePosY, MouseKey key, KeyStatus status) {status; key; MousePosX; MousePosY; }
	virtual void OnRender(Bitmap* renderTarget) = 0; 
}; 

#endif //WINDRAW_INPUT_HANDLER_H