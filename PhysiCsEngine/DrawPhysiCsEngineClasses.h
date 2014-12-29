#ifndef PCE_DRAWPHYSICSENGINECLASSES_H
#define PCE_DRAWPHYSICSENGINECLASSES_H

#include "SphereCollider.h"

class DrawPhysiCsEngineClasses
{
public:
	DrawPhysiCsEngineClasses(void);
	~DrawPhysiCsEngineClasses(void);

	static void DrawBoundingSphere(const Sphere3DCollider* i_sphere);
};

#endif