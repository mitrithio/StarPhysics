#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "..\PCEUtilities\PCEUtilities.h"
#include "PositionableObject.h"
#include "Component.h"

class GameObject : public PositionableObject
{
public:
	GameObject(PCEVector2 i_position, float i_rotation, const PositionableObject * i_owner = nullptr);
	virtual ~GameObject(void);

	void addComponent(Component* io_component);

protected:
	PCEMap<ComponentType, PCEVector<Component*>*> m_components;

private:
	void removeComponents();
};

#endif