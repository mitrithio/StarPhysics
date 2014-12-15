#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "..\PCEUtilities\PCEUtilities.h"
#include "PositionableObject.h"
#include "Component.h"

class GameObject : public PositionableObject
{
public:
	
	GameObject(PCEPoint i_position, float i_rotation, PositionableObject * i_owner = nullptr);

	virtual ~GameObject(void);

	virtual void Update( float i_fDeltaTime );
	void RegisterComponent(Component* i_pComponent);

protected:

	GameObject();
	GameObject( const GameObject& i_other );
	GameObject& operator=( const GameObject& i_other );
	bool operator==( const GameObject& i_other ) const;
	bool operator!=( const GameObject& i_other ) const;

protected:
	typedef PCEVector<Component*>							VectorComponent;
	typedef VectorComponent::PCEIterator					VectorComponentIterator;
	typedef PCEMap<PCEObjectId, PCEVector<Component*>>		MapComponents;
	typedef MapComponents::PCEIterator						MapComponentsIterator;
	
	MapComponents m_mComponents;

private:
	void UnregisterComponents();
};

#endif