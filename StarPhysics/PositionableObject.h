#ifndef	POSITIONABLE_OBJECT_H
#define POSITIONABLE_OBJECT_H

#include "../PCEUtilities/PCEUtilities.h"

class PositionableObject
{
public:
	PositionableObject(PCEPoint3D i_oRelativePosition, double i_fRelativeRotation, bool i_bEnabled = true, PositionableObject * i_oOwner  = nullptr);
	virtual ~PositionableObject(void);

	double GetAbsoluteRotation() const;
	double GetRelativeRotation() const;
	bool IsEnable();
	void SetEnable( bool i_bVal );
	void SetRelativePosition( const PCEPoint3D& i_oPostion );
	const PCEPoint3D& GetRelativePosition();
	PCEPoint3D& GetEditableRelativePosition();
	PCEPoint3D GetAbsolutePosition();
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
	PCEPoint3D m_oRelativePosition;
	double m_fRelativeRotation;

private:
	PCEObjectId m_oId;

protected:
	bool m_bEnabled;

};

#endif