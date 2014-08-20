#ifndef	POSITIONABLE_OBJECT_H
#define POSITIONABLE_OBJECT_H

// #include "../PCEUtilities/PCEUtilities.h"
#include "../PCEUtilities/PCEVector.h"
#include "../PCEUtilities/PCEString.h"

class PositionableObject
{
public:
	PositionableObject(PCEVector2 i_oPosition, float i_fRotation, bool i_bEnabled = true, PositionableObject * i_oOwner  = nullptr);
	virtual ~PositionableObject(void);

	float GetAbsoluteRotation() const;
	float GetRelativeRotation() const;
	bool IsEnable();
	void SetEnable( bool i_bVal );
	void SetRelativePosition( PCEVector2 i_oPostion );
	const PCEVector2& GetRelativePosition();
	const PCEVector2& GetAbsolutePosition();
	const PositionableObject* GetOwner() const;

	const PCEString* GetID() const;
	void SetID(const char* i_ID);

protected:
	bool operator==(const PositionableObject& i_other);
	PositionableObject(const PositionableObject& i_other);

	PositionableObject * m_pParent;
	PCEVector2 m_oRelativePosition;
	PCEVector2 m_oAbsolutePosition;
	float m_fRelativeRotation;

private:
	const PCEString * m_spObjectID;

protected:
	bool m_bEnabled;

};

#endif