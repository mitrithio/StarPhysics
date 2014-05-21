#include "KeyboardStatus.h"
#include "WinDrawSystemApi.h"
#include "EventHandler.h"

namespace KeyboardStatus
{
	KeyStatus keys[256] = {KeyIdle}; 

	bool isKeyPressed(int KeyCode)
	{
		return keys[KeyCode] == KeyPressed; 
	}
	bool isKeyReleased(int KeyCode)
	{
		return keys[KeyCode] == KeyReleased; 
	}

	void Reset()
	{
		memset(keys, 0, sizeof(keys)); 
	}
	void OnInput(int KeyCode, KeyStatus status)
	{
		keys[KeyCode] = status; 
	}

}