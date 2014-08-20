#ifndef GAME_EVENT_HANDLER_CLASS
#define GAME_EVENT_HANDLER_CLASS

#include "../WinDraw/WinDraw.h"					//load the whole WinDraw library
#include <stdio.h>								//for sprintf

class GameEventHandler: public EventHandler
{
public: 
	GameEventHandler()
	{
		x = 320;
		CreateBitmaps();
	}

	~GameEventHandler()
	{
		DestroyBitmaps();
	}

	void OnInput(unsigned int Key, KeyStatus status)
	{
		if(status != KeyReleased) return; 
		if(Key == VK_LEFT) x-=10; 
		if(Key == VK_RIGHT) x+=10; 
	} 

	void OnMouseInput(int MousePosX, int MousePosY, MouseKey key, KeyStatus status)
	{
		if (key == LMouse && MousePosY >= 225 && MousePosY <= 665 && status != KeyPressed){
		char buffer[256]; 
		sprintf_s(buffer, "Mouse input ( %i, %i) %s %s\n", MousePosX, MousePosY, 
								key == No_Key ? "No Key": (key == LMouse ? "LMouse": "RMouse"), 
								status == KeyPressed ? "pressed." : (status == MouseMove ? "moved." : "released.")); 
		OutputDebugStringA(buffer); 
		}
	}

	void OnRender(Bitmap* renderTarget)
	{ 
		m_oBackgroundImg->DrawTo(renderTarget,0,0);
		renderTarget->RenderText(x, 240, "some text", 255, 255, 255); 
	}

private: 
	int x;
	Bitmap * m_oBackgroundImg;

	void CreateBitmaps()
	{
		m_oBackgroundImg = new Bitmap("startScreen.tga");
	}

	void DestroyBitmaps()
	{
		delete m_oBackgroundImg;
	}
};

#endif //GAME_EVENT_HANDLER_CLASS