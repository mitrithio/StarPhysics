#ifdef _DEBUG	// _DEBUG: memory leak detection

/*
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW      //redefinition of new in _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )      
#define new DBG_NEW   
#endif	// redefinition of new
*/

#include "vld.h"

#endif  // end _DEBUG

#include "../WinDraw/WinDraw.h"					//load the whole WinDraw library
#include "../PhysiCsEngine/PCE.h"				//load the whole PCE library
#include "../PCEUtilities/PCEUtilities.h"		//load the whole PCEUtilities library
#include "GameEventHandler.h"
#include <stdio.h>

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{ 
	/*	
	//only for _DEBUG: when application exit, this function will stamp if memory leaks are detected
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 
	*/

	MainWindow mainWindow;
	mainWindow.Create(1024,768,"StarPhysics");

	const float secondsPerFrame = (1.f / 60.f); 
	Timer t;

	GameEventHandler *eventHandler = new GameEventHandler();

	mainWindow.SetEventHandler(eventHandler);

	BoundingSphere *bs = new BoundingSphere(10,0,0);

	bs->setSubShapesInitialCapacity(10);
	BoundingSphere bssubs[10] = {BoundingSphere(1,0,0), BoundingSphere(1,0,0), BoundingSphere(1,0,0), BoundingSphere(1,0,0), BoundingSphere(1,0,0), BoundingSphere(1,0,0), BoundingSphere(1,0,0), BoundingSphere(1,0,0), BoundingSphere(1,0,0), BoundingSphere(1,0,0)};

	bs->addSubShapeArray(bssubs, 10);

	for (int i = 0; i < 10; ++i)
	{
		BoundingSphere *bssubs2 = new BoundingSphere(1,0,0);
		bs->addSubShape(*bssubs2);
		delete bssubs2;
	}
	
	bs->addSubSphere(1,2,2);

	DrawPhysiCsEngineClasses::DrawBoundingSphere(*bs);
	
	char buffer[256]; 
	
	PCEString stringa("ciao");
	
	PCEString secondStr(" sono scemo");
	stringa += secondStr;
	
	stringa += " vero Fabri?\n";
	sprintf_s(buffer, *stringa); 
	OutputDebugStringA(buffer);

	while(mainWindow.IsAlive())		 
	{
		t.TimeFromLast();

		mainWindow.DispatchInput(); 
		mainWindow.Redraw();

		wait(secondsPerFrame - t.TimeFromLast());
	}

	mainWindow.ClearEventHandler();
	delete bs;
	delete eventHandler;
	return 0;
}