#include <stdio.h>
#include "DrawPhysiCsEngineClasses.h"
#include "SphereCollider.h"


DrawPhysiCsEngineClasses::DrawPhysiCsEngineClasses(void)
{
}


DrawPhysiCsEngineClasses::~DrawPhysiCsEngineClasses(void)
{
}

void DrawPhysiCsEngineClasses::DrawBoundingSphere(const Sphere3DCollider* i_sphere)
{
	char buffer[256]; 
	sprintf_s(buffer, "Sphere3DCollider: %f, %f, %f; radius: %f\n", i_sphere->getCenter()[0], i_sphere->getCenter()[1], i_sphere->getCenter()[2], i_sphere->getRadius()); 
	OutputDebugStringA(buffer);

   	const PCEVector<Shape *> tpSubs = i_sphere->GetSubShapes();
   	if (!tpSubs.empty())
   	{
   		sprintf_s(buffer, "*** SubSpheres: *** \n"); 
   		OutputDebugStringA(buffer);
   		for(uint32_t i = 0; i < tpSubs.size(); ++i)
   		{
 			if (tpSubs.at(i) != nullptr)
 			{
 				DrawBoundingSphere(static_cast<const Sphere3DCollider*>(tpSubs.at(i)));
 			}
   		}
   	}
}