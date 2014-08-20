#include "PositionableObject.h"


PositionableObject::PositionableObject(PCEVector2 i_position, float i_rotation, bool i_isEnabled/* = true*/, PositionableObject * i_owner/* = nullptr*/)
	: m_pParent(i_owner)
	, m_oRelativePosition(i_position)
	, m_fRelativeRotation(i_rotation)
	, m_bEnabled(i_isEnabled)
	, m_spObjectID(nullptr)
{
	m_oAbsolutePosition = m_pParent->GetAbsolutePosition() + m_oRelativePosition;
}


PositionableObject::~PositionableObject(void)
{
	delete m_spObjectID;
}

float PositionableObject::GetAbsoluteRotation() const
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

float PositionableObject::GetRelativeRotation() const
{
	return m_fRelativeRotation;
}

void PositionableObject::SetRelativePosition( PCEVector2 i_oPostion )
{
	m_oRelativePosition = i_oPostion;
	m_oAbsolutePosition = m_pParent->GetAbsolutePosition() + m_oRelativePosition;
}

const PCEVector2& PositionableObject::GetRelativePosition()
{
	return m_oRelativePosition;
}

const PCEVector2& PositionableObject::GetAbsolutePosition()
{
	return m_oAbsolutePosition;
}

const PositionableObject* PositionableObject::GetOwner() const
{
	return m_pParent;
}

const PCEString* PositionableObject::GetID() const
{
	return m_spObjectID;
}

void PositionableObject::SetID( const char* i_ID )
{
	if (m_spObjectID == nullptr)
	{
		m_spObjectID = new PCEString( i_ID );
	}
}
