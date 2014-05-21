#ifndef PCE_DRAWPHYSICSENGINECLASSES_H
#define PCE_DRAWPHYSICSENGINECLASSES_H

#include "BoundingSphere.h"

class DrawPhysiCsEngineClasses
{
public:
	DrawPhysiCsEngineClasses(void);
	~DrawPhysiCsEngineClasses(void);

	static void DrawBoundingSphere(const BoundingSphere &i_sphere);
};

#endif