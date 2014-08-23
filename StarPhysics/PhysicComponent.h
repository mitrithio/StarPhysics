#ifndef	PHYSIC_COMPONENT_H
#define PHYSIC_COMPONENT_H

#include "Component.h"
#include "../PCEUtilities/PCEUtilities.h"
#include "../PhysiCsEngine/PCE.h"

class PhysicComponent : Component
{
public:
	PhysicComponent(PCEVector2 i_oPosition, float i_fRotation, bool i_bEnabled = true, PositionableObject * i_oOwner = nullptr);
	~PhysicComponent(void);

	void update(float i_deltaTime = 0);

	void addShape(Shape & io_shape);
	bool removeShape(Shape & io_shape);

private:
	PCEVector<Shape*> m_oShapes;
};

#endif