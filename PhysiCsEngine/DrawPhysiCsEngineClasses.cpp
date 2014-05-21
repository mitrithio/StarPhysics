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

	const BoundingSphere *tpSubs = i_sphere.getSubSpheres();
	if (tpSubs != nullptr)
	{
		sprintf_s(buffer, "*** SubSpheres: *** \n"); 
		OutputDebugStringA(buffer);
		for(int i = 0; i < i_sphere.getSubSpheresCount(); ++i)
		{
			DrawBoundingSphere(tpSubs[i]);
		}
	}
}