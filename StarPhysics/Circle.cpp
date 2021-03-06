#include "Circle.h"

Circle::Circle()
	: GameObject()
	, m_uiLevel(0)
{
}

Circle::Circle( PCEPoint3D i_oPosition, double i_fRotation )
	: GameObject( i_oPosition, i_fRotation, nullptr )
	, m_uiLevel( 0 )
{
}

Circle::Circle( const Circle& i_oCircle )
	: GameObject( i_oCircle )
	, m_uiLevel( 0 )
{
}

Circle::~Circle(void)
{
}

void Circle::setLevel(unsigned int i_uiLevel)
{
	m_uiLevel = i_uiLevel;
}

Circle& Circle::operator=( const Circle& i_other )
{
	if ( this != &i_other )
	{
		GameObject::operator=( i_other );
		m_uiLevel = i_other.m_uiLevel;
	}

	return *this;
}

bool Circle::operator==( const Circle& i_other ) const
{
	return ( 
			GameObject::operator==(i_other)		&&
			m_uiLevel == i_other.m_uiLevel
			);
}

bool Circle::operator!=( const Circle& i_other ) const
{
	return !(*this == i_other);
}

unsigned int Circle::getLevel() const
{
	return m_uiLevel;
}
