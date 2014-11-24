#include "PhysicComponent.h"


PhysicComponent::PhysicComponent(PCEVector2 i_position, float i_rotation, bool i_isEnabled /* = true */, PositionableObject * i_owner /* = nullptr */)
	: Component(PHYSIC_COMPONENT, i_position, i_rotation, i_isEnabled, i_owner)
{
}


PhysicComponent::~PhysicComponent(void)
{
}

void PhysicComponent::update(float i_deltaTime /* = 0 */)
{

}

void PhysicComponent::addShape(Shape & io_shape)
{
	m_oShapes.push_back(&io_shape);
}

bool PhysicComponent::removeShape(Shape & io_shape)
{
	bool founded = false;
	for(unsigned int index = 0; !founded && index < m_oShapes.size(); ++index)
	{
		if (m_oShapes[index] == &io_shape)
		{
			founded = true;
			m_oShapes.erase(index);
		}
	}

	return founded;
}
