#ifdef _DEBUG	// _DEBUG: memory leak detection
//#include "vld.h"
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
#include "CirclesController.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{ 
	MainWindow oMainWindow;
	oMainWindow.Create(1024,768,"StarPhysics");

	const float fSecondsPerFrame = (1.f / 60.f); 
	Timer oTimer;

	GameEventHandler *pEventHandler = new GameEventHandler();

	oMainWindow.SetEventHandler(pEventHandler);

	// TESTING:

	while(oMainWindow.IsAlive())
	{
		oTimer.TimeFromLast();

		oMainWindow.DispatchInput(); 
		oMainWindow.Redraw();

		wait(fSecondsPerFrame - oTimer.TimeFromLast());
	}

	oMainWindow.ClearEventHandler();
	delete pEventHandler;
	return 0;
}