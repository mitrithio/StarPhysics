#include "CirclesController.h"
#include "Circle.h"


CirclesController::CirclesController(void)
{
}


CirclesController::~CirclesController(void)
{
}

void CirclesController::CreateCircle( PCEVector2 i_oPosition, float i_fRotation )
{
	Circle oCircle( i_oPosition, i_fRotation );
	oCircle.SetEnable(false);
	PCEString sKey("Circle");
	sKey += PCEString::intToString( m_voCircles.size() + 1 );
	oCircle.SetID( sKey.getStringAsChar() );
	m_voCircles[sKey] = oCircle;
}
