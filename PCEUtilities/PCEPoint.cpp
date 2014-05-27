#include "PCEPoint.h"

inline bool PCEPoint::operator== (const PCEPoint& rvalue) const		
{
	return mX == rvalue.mX && mY == rvalue.mY && mZ == rvalue.mZ;
}

inline bool PCEPoint::operator!= (const PCEPoint& rvalue) const		
{
	return !(*this == rvalue);
}	

PCEPoint& PCEPoint::operator=(const PCEPoint& rvalue)
{
	if (*this != rvalue)
	{
		mX = rvalue.mX; 
		mY = rvalue.mY; 
		mZ = rvalue.mZ;
	}
	return *this;
}

const float* PCEPoint::getCoordinates() const
{
	float tmp[3] = {mX, mY, mZ};
	return tmp;
}
