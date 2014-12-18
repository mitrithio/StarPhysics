#ifndef	PHYSIC_COMPONENT_H
#define PHYSIC_COMPONENT_H

#include "Component.h"
#include "../PCEUtilities/PCEUtilities.h"
#include "../PhysiCsEngine/PCE.h"

class PhysicComponent : public Component
{
public:
	PhysicComponent(PCEPoint i_oPosition, double i_fRotation, bool i_bEnabled = true, PositionableObject * i_oOwner = nullptr);
	~PhysicComponent(void);

	void update( double i_deltaTime = 0 );

	void addShape( Shape & io_shape );
	bool removeShape( Shape & io_shape );

private:
	PCEVector<Shape*> m_oShapes;
};

#endif