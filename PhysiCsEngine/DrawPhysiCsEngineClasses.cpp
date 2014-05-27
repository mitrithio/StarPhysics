#include <stdio.h>
#include "DrawPhysiCsEngineClasses.h"


DrawPhysiCsEngineClasses::DrawPhysiCsEngineClasses(void)
{
}


DrawPhysiCsEngineClasses::~DrawPhysiCsEngineClasses(void)
{
}

void DrawPhysiCsEngineClasses::DrawBoundingSphere(const BoundingSphere &i_sphere)
{
	char buffer[256]; 
	sprintf_s(buffer, "BoundingSphere: %f, %f, %f; radius: %f\n", i_sphere.getCenter().mX, i_sphere.getCenter().mY,i_sphere.getCenter().mZ, i_sphere.getRadius()); 
	OutputDebugStringA(buffer);

//  	const PCEVector<Shape *> * tpSubs = new PCEVector<Shape *>(i_sphere.getSubShapes());
//  	if (!tpSubs->empty())
//  	{
//  		sprintf_s(buffer, "*** SubSpheres: *** \n"); 
//  		OutputDebugStringA(buffer);
//  		for(int i = 0; i < tpSubs->size(); ++i)
//  		{
//  			DrawBoundingSphere(*static_cast<const BoundingSphere*>(tpSubs->at(i)));
//  		}
//  	}
}