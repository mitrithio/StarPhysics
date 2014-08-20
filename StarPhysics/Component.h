#ifndef	COMPONENT_H
#define COMPONENT_H

#include "../PCEUtilities/PCEVector.h"
#include "PositionableObject.h"

enum ComponentType
{
	PHYSIC = 0,
	GRAPHIC,

	numOFID
};

class Component : public PositionableObject
{
public:
	Component(ComponentType i_type, PCEVector2 i_position, float i_rotation, bool i_isEnabled = true, const PositionableObject * i_owner = nullptr) 
		: PositionableObject(i_position, i_rotation, i_isEnabled, i_owner)
		, m_type(i_type)
	{}

	virtual ~Component(){}

	virtual void update(float i_deltaTime = 0) = 0;

	const ComponentType getType() const			{return m_type;}

protected:
	ComponentType m_type;
};

#endif