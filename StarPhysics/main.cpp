#ifdef _DEBUG	// _DEBUG: memory leak detection
#include "vld.h"
#endif  // end _DEBUG

/*
	RISULTATI TEST:
	1. PCEString		-->	OK
	2. PCEVector		-->	OK
	3. BoundingSphere	-->
*/

#include "../WinDraw/WinDraw.h"					//load the whole WinDraw library
#include "../PhysiCsEngine/PCE.h"				//load the whole PCE library
#include "../PCEUtilities/PCEUtilities.h"		//load the whole PCEUtilities library
#include "GameEventHandler.h"
#include <stdio.h>

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{ 
	MainWindow mainWindow;
	mainWindow.Create(1024,768,"StarPhysics");

	const float secondsPerFrame = (1.f / 60.f); 
	Timer t;

	GameEventHandler *eventHandler = new GameEventHandler();

	mainWindow.SetEventHandler(eventHandler);

	// TESTING:

	while(mainWindow.IsAlive())		 
	{
		t.TimeFromLast();

		mainWindow.DispatchInput(); 
		mainWindow.Redraw();

		wait(secondsPerFrame - t.TimeFromLast());
	}

	mainWindow.ClearEventHandler();
	delete eventHandler;
	return 0;
}