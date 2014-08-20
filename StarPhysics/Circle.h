#ifndef CIRCLE_H
#define CIRCLE_H

#include "gameobject.h"
#include "../PCEUtilities/PCEUtilities.h"

class Circle :
	public GameObject
{
public:
	Circle( PCEVector2 i_oPosition, float i_fRotation );
	~Circle(void);

	void setLevel(unsigned int i_uiLevel);
	const unsigned int getLevel() const;

private:
	static const PCEString STRING_IMAGE_PATH;

	unsigned int m_uiLevel;
	PCEString m_sImagePath;
};

const PCEString Circle::STRING_IMAGE_PATH = "/images/circle";

#endif