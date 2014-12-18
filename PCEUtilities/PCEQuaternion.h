#ifndef PCEQUATERNION_H
#define PCEQUATERNION_H

#include "PCEVector3.h"

class PCEQuaternion
{
public:

	PCEQuaternion();

	PCEQuaternion( const PCEHVector3& i_vEulerAngles );

	PCEQuaternion( double a, double b, double c, double d );

	PCEQuaternion( const double* i_fDimensions );

	PCEQuaternion( const PCEQuaternion& i_other );

	~PCEQuaternion();

	PCEQuaternion& operator+=(const PCEQuaternion& i_other);

	PCEQuaternion operator+(const PCEQuaternion& i_other) const;

	PCEQuaternion& operator-=(const PCEQuaternion& i_other);

	PCEQuaternion operator-(const PCEQuaternion& i_other) const;

	PCEQuaternion& operator*=(const PCEQuaternion& i_other);

	PCEQuaternion operator*(const PCEQuaternion& i_other) const;

	PCEQuaternion& operator*=(double i_fScalar);

	PCEQuaternion operator*(double i_fScalar) const;

	PCEQuaternion& operator/=(double i_fScalar);

	PCEQuaternion operator/(double i_fScalar) const;

	double& operator[](unsigned int i_uiIndex) const;

	double Module();
	
	PCEQuaternion Normal();

	PCEHVector3 EulerAngle();

private:

	double* m_mQuaternion;
};

#endif // PCEQUATERNION_H