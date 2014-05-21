#ifndef WINDRAW_MAIN_WINDOW_H
#define WINDRAW_MAIN_WINDOW_H

#include "WinDrawSystemApi.h"

class EventHandler; 

class MainWindow
{	
protected: 
	HWND handle; //windows stuff
	EventHandler* eventHandler; 
public: 
	MainWindow(): handle(NULL), eventHandler(NULL){}	
	~MainWindow(){} 

	void Create(int w, int h, char* title);		//creates a top-level window (size w * h), whose caption is "title". 
	void Destroy() { DestroyWindow(handle); }	//Destroys the window. 
	bool IsAlive() { return handle != NULL; }	//true if the window still exists, false otherwise. 

	void SetEventHandler(EventHandler* newEventHandler) { eventHandler = newEventHandler; }
	void ClearEventHandler() { eventHandler = NULL; }	//removes the event handler. 

	void DispatchInput(); //causes EventHandler::OnInput to be called. 
	void Redraw();		  //causes EventHandler::OnRender to be called. 	

	static LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ); //Windows message procedure. 
}; 

#endif // WINDRAW_MAIN_WINDOW_H