#include "GameObject.h"
#include <assert.h>

GameObject::GameObject(PCEVector2 i_position, float i_rotation, PositionableObject * i_owner /*= nullptr*/)
	: PositionableObject(i_position, i_rotation, false, i_owner)
{
}

GameObject::~GameObject(void)
{
	UnregisterComponents();
}

void GameObject::RegisterComponent(Component* i_pComponent)
{
	assert(i_pComponent != nullptr);
	m_mComponents[i_pComponent->getType()].push_back(i_pComponent);
}

void GameObject::UnregisterComponents()
{
	for ( PCEMap<ComponentType, PCEVector<Component*>>::PCEIterator it = m_mComponents.begin(); it != m_mComponents.end(); ++it )
	{
		(*it).second.clear();
	}
	m_mComponents.clear();
}

void GameObject::Update( float i_fDeltaTime )
{
	for ( MapComponentsIterator itVector = m_mComponents.begin(); itVector != m_mComponents.end(); ++itVector )
	{
		for ( VectorComponentIterator itComponent = (*itVector).second.begin(); itComponent != (*itVector).second.end(); ++itComponent )
		{
			(*itComponent)->update( i_fDeltaTime );
		}
	}
}

// PROTECTED:

GameObject::GameObject()
	: PositionableObject()
{
}

GameObject::GameObject( const GameObject& i_other )
	: PositionableObject( i_other )
	, m_mComponents( i_other.m_mComponents )
{
}

GameObject& GameObject::operator=( const GameObject& i_other )
{
	if ( this != &i_other )
	{
		PositionableObject::operator=( i_other);
		m_mComponents = i_other.m_mComponents;
	}
	return *this;
}

bool GameObject::operator==( const GameObject& i_other )
{
	return (
		PositionableObject::operator==(i_other)	&&
		m_mComponents == i_other.m_mComponents
		);
}

bool GameObject::operator!=( const GameObject& i_other )
{
	return !( *this == i_other );
}