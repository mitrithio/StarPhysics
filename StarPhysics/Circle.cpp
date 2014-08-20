#include "Circle.h"



Circle::Circle( PCEVector2 i_oPosition, float i_fRotation )
	: GameObject( i_oPosition, i_fRotation, this )
{
}


Circle::~Circle(void)
{
}


void Circle::setLevel(unsigned int i_uiLevel)
{
	m_uiLevel = i_uiLevel;
	m_sImagePath = STRING_IMAGE_PATH + PCEString::intToString(i_uiLevel) + ".tga";
}