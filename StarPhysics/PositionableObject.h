#ifndef	POSITIONABLE_OBJECT_H
#define POSITIONABLE_OBJECT_H

#include "../PCEUtilities/PCEUtilities.h"

class PositionableObject
{
public:
	PositionableObject(PCEVector2 i_oRelativePosition, float i_fRelativeRotation, bool i_bEnabled = true, PositionableObject * i_oOwner  = nullptr);
	virtual ~PositionableObject(void);

	float GetAbsoluteRotation() const;
	float GetRelativeRotation() const;
	bool IsEnable();
	void SetEnable( bool i_bVal );
	void SetRelativePosition( PCEVector2 i_oPostion );
	const PCEVector2& GetRelativePosition();
	const PCEVector2& GetAbsolutePosition();
	const PositionableObject* GetOwner() const;

	const PCEObjectId& GetID() const;
	void SetID(const char* i_ID);

protected:

	PositionableObject();
	PositionableObject(const PositionableObject& i_other);
	PositionableObject& operator=(const PositionableObject& i_other);
	bool operator==(const PositionableObject& i_other) const;
	bool operator!=(const PositionableObject& i_other) const;

protected:

	PositionableObject * m_pParent;
	PCEVector2 m_oRelativePosition;
	float m_fRelativeRotation;

private:
	PCEObjectId m_oId;

protected:
	bool m_bEnabled;

};

#endif