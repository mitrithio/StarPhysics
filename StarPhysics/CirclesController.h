#ifndef CIRCLECONTROLLER_H
#define CIRCLECONTROLLER_H

#include "../PCEUtilities/PCEUtilities.h"

class Circle;

class CirclesController
{
public:
	CirclesController(void);
	~CirclesController(void);

	const Circle* GetCircle();
	void CreateCircle(PCEVector2 i_oPosition, float i_fRotation);

private:

	PCEMap<PCEString, Circle> m_voCircles;


	struct NodeFreeCircle
	{
		Circle* pNode;
		Circle* pNext;
	};
};

#endif