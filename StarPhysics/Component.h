#ifndef	COMPONENT_H
#define COMPONENT_H

#include "../PCEUtilities/PCEVector.h"
#include "PositionableObject.h"

class Component : public PositionableObject
{
public:
	Component(const PCEObjectId& i_type, PCEVector2 i_position, float i_rotation, bool i_isEnabled = true, PositionableObject * i_owner = nullptr);

	virtual ~Component();

	virtual void update(float i_deltaTime = 0) = 0;

	const PCEObjectId& getType() const;

protected:
	PCEObjectId m_eType;
};

static const PCEObjectId GRAPHIC_COMPONENT("GRAPHIC");
static const PCEObjectId PHYSIC_COMPONENT("PHYSIC");

#endif