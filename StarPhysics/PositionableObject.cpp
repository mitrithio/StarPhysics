#include "PositionableObject.h"

#include <float.h>
#include "..\PCEUtilities\PCEPoint.h"


PositionableObject::PositionableObject( PCEPoint i_oRelativePosition, double i_fRelativeRotation, bool i_isEnabled/* = true*/, PositionableObject * i_owner/* = nullptr*/ )
	: m_pParent( i_owner )
	, m_oRelativePosition( i_oRelativePosition )
	, m_fRelativeRotation( i_fRelativeRotation )
	, m_bEnabled( i_isEnabled )
	, m_oId( INVALID_OBJECT_ID )
{
}

PositionableObject::~PositionableObject(void)
{
}

double PositionableObject::GetAbsoluteRotation() const
{
	if (m_pParent != nullptr)
	{
		return m_fRelativeRotation + m_pParent->GetAbsoluteRotation();
	}

	return m_fRelativeRotation;
}

bool PositionableObject::IsEnable()
{
	return m_bEnabled;
}

void PositionableObject::SetEnable( bool i_bVal )
{
	m_bEnabled = i_bVal;
}

double PositionableObject::GetRelativeRotation() const
{
	return m_fRelativeRotation;
}

void PositionableObject::SetRelativePosition( const PCEPoint& i_oPostion )
{
	m_oRelativePosition = i_oPostion;
}

const PCEPoint& PositionableObject::GetRelativePosition()
{
	return m_oRelativePosition;
}

PCEPoint& PositionableObject::GetEditableRelativePosition()
{
	return m_oRelativePosition;
}

PCEPoint PositionableObject::GetAbsolutePosition()
{
	if (m_pParent != nullptr)
	{
		return m_oRelativePosition + m_pParent->GetAbsolutePosition();
	}

	return m_oRelativePosition;
}

const PositionableObject* PositionableObject::GetOwner() const
{
	return m_pParent;
}

const PCEObjectId& PositionableObject::GetID() const
{
	return m_oId;
}

void PositionableObject::SetID( const char* i_ID )
{
	if ( i_ID )
	{
		PCEObjectId temp( i_ID );
		m_oId = temp;
	}
}

// PROTECTED:

PositionableObject::PositionableObject()
	: m_pParent(nullptr)
	, m_oRelativePosition( INVALID_POINT )
	, m_fRelativeRotation( DBL_MAX )
	, m_bEnabled(false)
	, m_oId(INVALID_OBJECT_ID)
{
}

PositionableObject::PositionableObject( const PositionableObject& i_other )
	: m_pParent( i_other.m_pParent )
	, m_oRelativePosition( i_other.m_oRelativePosition )
	, m_fRelativeRotation( i_other.m_fRelativeRotation )
	, m_bEnabled( i_other.m_bEnabled )
	, m_oId( i_other.m_oId ) 
{
}

PositionableObject& PositionableObject::operator=( const PositionableObject& i_other )
{
	if ( this != &i_other )
	{
		m_oId = i_other.m_oId;
		m_pParent = i_other.m_pParent;
		m_oRelativePosition = i_other.m_oRelativePosition;
		m_fRelativeRotation = i_other.m_fRelativeRotation;
		m_bEnabled = i_other.m_bEnabled;
	}

	return *this;
}

bool PositionableObject::operator==( const PositionableObject& i_other ) const
{
	return ( 
		m_oId == i_other.m_oId				&&
		m_pParent == i_other.m_pParent						&&
		m_oRelativePosition == i_other.m_oRelativePosition &&
		m_fRelativeRotation == i_other.m_fRelativeRotation &&
		m_bEnabled == i_other.m_bEnabled
		);
}

bool PositionableObject::operator!=( const PositionableObject& i_other ) const
{
	return !(*this == i_other);
}