#include "GameObject.h"
#include <assert.h>

GameObject::GameObject(PCEVector2 i_position, float i_rotation, const PositionableObject * i_owner  = nullptr)
	: PositionableObject(i_position, i_rotation, i_owner)
{
}


GameObject::~GameObject(void)
{
	removeComponents();
}

void GameObject::addComponent(Component* io_component)
{
	assert(io_component != nullptr);
	m_components[io_component->getType()]->push_back(io_component);
}

void GameObject::removeComponents()
{
	m_components.clear();
}
