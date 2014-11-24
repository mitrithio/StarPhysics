#ifndef CIRCLECONTROLLER_H
#define CIRCLECONTROLLER_H

#include "../PCEUtilities/PCEUtilities.h"
#include <float.h>
#include "Circle.h"

class CirclesController
{
public:
	CirclesController();
	CirclesController( unsigned int i_uiNumberOfCircles );

	~CirclesController();

	const PCEObjectId& GetNextFreeCircleID();
	void SetCircleFree( const PCEObjectId& i_oCircleId, bool i_bFree );
	void CreateCircle( PCEVector2 i_oPosition, float i_fRotation );

	void CreateCirclePool( unsigned int i_uiNumberOfCircle );

	void Update( float i_fDeltaTime = 0 );

private:

	PCEVector<bool>					m_vIsCircleFree;
	PCEMap<PCEObjectId, Circle*>	m_oCirclesMap;
	unsigned int					m_uiNextCircleFree;

	static const PCEString		IMAGES_CIRCLE_PATH;
};

static const Circle INVALID_CIRCLE( PCEVector2( FLT_MAX, FLT_MAX ), FLT_MAX );

#endif