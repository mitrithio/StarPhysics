#include "Component.h"

const PCEObjectId& Component::getType() const
{
	return m_eType;
}

Component::~Component()
{

}

Component::Component( const PCEObjectId& i_type, PCEPoint i_position, float i_rotation, bool i_isEnabled /*= true*/, PositionableObject * i_owner /*= nullptr*/ )
	: PositionableObject(i_position, i_rotation, i_isEnabled, i_owner)
	, m_eType(i_type)
{

}
