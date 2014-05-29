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

// 	BoundingSphere *bs = new BoundingSphere(10,0,0);
// 
// 	BoundingSphere *bssubs = new BoundingSphere[10];
// 	BoundingSphere *newBS = new BoundingSphere(1,1,1);
// 	for (int i = 0; i < 10; ++i)
// 	{
// 		bssubs[i] = *newBS;
// 	}
// 
// 	DrawPhysiCsEngineClasses::DrawBoundingSphere(*newBS);
// 
// 	//BoundingSphere bssubs[10] = {BoundingSphere(1,0,0), BoundingSphere(1,0,0), BoundingSphere(1,0,0), BoundingSphere(1,0,0), BoundingSphere(1,0,0), BoundingSphere(1,0,0), BoundingSphere(1,0,0), BoundingSphere(1,0,0), BoundingSphere(1,0,0), BoundingSphere(1,0,0)};
// 
// 	PCEVector<BoundingSphere> vBoundingSphere(bssubs, 10);
// 
// 	bs->addSubShapeArray(bssubs, 10);
// 
// 	for (int i = 0; i < 10; ++i)
// 	{
// 		BoundingSphere *bssubs2 = new BoundingSphere(1,0,0);
// 		bs->addSubShape(*bssubs2);
// 		vBoundingSphere.push_back(*bssubs2);
// 		delete bssubs2;
// 	}
// 	
// 	bs->addSubSphere(1,2,2);
// 	vBoundingSphere.push_back(*new BoundingSphere(1,2,2));
// 
// 	DrawPhysiCsEngineClasses::DrawBoundingSphere(*bs);
// 	
// 	const PCEVector<Shape *> * tp = bs->getSubShapes();
// 
// 	for (unsigned int i = 0; i < tp->size(); ++i)
// 	{
// 		DrawPhysiCsEngineClasses::DrawBoundingSphere(*static_cast<BoundingSphere *>(tp->at(i)));
// 		//DrawPhysiCsEngineClasses::DrawBoundingSphere(vBoundingSphere[i]);
// 	}

	while(mainWindow.IsAlive())		 
	{
		t.TimeFromLast();

		mainWindow.DispatchInput(); 
		mainWindow.Redraw();

		wait(secondsPerFrame - t.TimeFromLast());
	}

	mainWindow.ClearEventHandler();
	//delete bs;
	delete eventHandler;
	return 0;
}