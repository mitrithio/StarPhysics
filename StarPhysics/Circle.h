#ifndef CIRCLE_H
#define CIRCLE_H

#include "gameobject.h"
#include "../PCEUtilities/PCEUtilities.h"

class Circle : public GameObject
{
public:
	Circle();
	Circle( const Circle& i_oCircle );
	Circle( PCEPoint3D i_oPosition, double i_fRotation );
	~Circle(void);

	void setLevel(unsigned int i_uiLevel);
	unsigned int getLevel() const;

	bool operator==( const Circle& i_other ) const;
	bool operator!=( const Circle& i_other ) const;
	Circle& operator=( const Circle& i_other );

private:

	unsigned int m_uiLevel;
};

#endif