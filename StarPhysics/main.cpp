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
   	BoundingSphere *bs = new BoundingSphere(10,0,0);

	DrawPhysiCsEngineClasses::DrawBoundingSphere(bs);

	PCEVector<Shape *> bsSub(10);

	Shape** arrayShape = new Shape*[11];

	for(int index = 0; index < 10; ++index)
	{
		arrayShape[index] = new BoundingSphere(7,27,42);
	}

	arrayShape[10] = new BoundingSphere(5,18,120);

	bsSub.push_back(arrayShape, 11);

	bs->addSubShape(bsSub);

	bs->addSubShape(arrayShape, 11);

	DrawPhysiCsEngineClasses::DrawBoundingSphere(bs);
   	

	while(mainWindow.IsAlive())		 
	{
		t.TimeFromLast();

		mainWindow.DispatchInput(); 
		mainWindow.Redraw();

		wait(secondsPerFrame - t.TimeFromLast());
	}

	mainWindow.ClearEventHandler();
	delete bs;
	for (int i = 0; i < 11; ++i)
	{
		delete arrayShape[i];
	}
	delete arrayShape;
	delete eventHandler;
	return 0;
}