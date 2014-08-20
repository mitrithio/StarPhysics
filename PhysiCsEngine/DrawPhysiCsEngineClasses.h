#ifndef PCE_DRAWPHYSICSENGINECLASSES_H
#define PCE_DRAWPHYSICSENGINECLASSES_H

#include "SphereCollider.h"

class DrawPhysiCsEngineClasses
{
public:
	DrawPhysiCsEngineClasses(void);
	~DrawPhysiCsEngineClasses(void);

	static void DrawBoundingSphere(const SphereCollider* i_sphere);
};

#endif