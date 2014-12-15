#include "PCEQuaternion.h"
#include <math.h>

PCEQuaternion::PCEQuaternion( float a, float b, float c, float d )
{
	m_mQuaternion = new float[4]();
	m_mQuaternion[0] = a;
	m_mQuaternion[1] = b;
	m_mQuaternion[2] = c;
	m_mQuaternion[3] = d;
}

PCEQuaternion::PCEQuaternion( const PCEQuaternion& i_other )
{
	m_mQuaternion = new float[4]();
	m_mQuaternion[0] = i_other.m_mQuaternion[0];
	m_mQuaternion[1] = i_other.m_mQuaternion[1];
	m_mQuaternion[2] = i_other.m_mQuaternion[2];
	m_mQuaternion[3] = i_other.m_mQuaternion[3];
}

PCEQuaternion::~PCEQuaternion()
{
	delete [] m_mQuaternion;
}

PCEQuaternion& PCEQuaternion::operator+=(const PCEQuaternion& i_other)
{
	m_mQuaternion[0] += i_other.m_mQuaternion[0];
	m_mQuaternion[1] += i_other.m_mQuaternion[1];
	m_mQuaternion[2] += i_other.m_mQuaternion[2];
	m_mQuaternion[3] += i_other.m_mQuaternion[3];
	return *this;
}

PCEQuaternion PCEQuaternion::operator+(const PCEQuaternion& i_other) const
{
	PCEQuaternion oRes = *this;
	oRes += i_other;
	return oRes;
}

PCEQuaternion& PCEQuaternion::operator-=(const PCEQuaternion& i_other)
{
	m_mQuaternion[0] -= i_other.m_mQuaternion[0];
	m_mQuaternion[1] -= i_other.m_mQuaternion[1];
	m_mQuaternion[2] -= i_other.m_mQuaternion[2];
	m_mQuaternion[3] -= i_other.m_mQuaternion[3];
	return *this;
}

PCEQuaternion PCEQuaternion::operator-(const PCEQuaternion& i_other) const
{
	PCEQuaternion oRes = *this;
	oRes -= i_other;
	return oRes;
}

PCEQuaternion& PCEQuaternion::operator*=(const PCEQuaternion& i_other)
{
	float A = m_mQuaternion[0] * i_other.m_mQuaternion[0] - m_mQuaternion[1] * i_other.m_mQuaternion[1] - m_mQuaternion[2] * i_other.m_mQuaternion[2] - m_mQuaternion[3] * i_other.m_mQuaternion[3];
	float B = m_mQuaternion[0] * i_other.m_mQuaternion[1] + m_mQuaternion[1] * i_other.m_mQuaternion[0] + m_mQuaternion[2] * i_other.m_mQuaternion[3] - m_mQuaternion[3] * i_other.m_mQuaternion[2];
	float C = m_mQuaternion[0] * i_other.m_mQuaternion[2] - m_mQuaternion[1] * i_other.m_mQuaternion[3] + m_mQuaternion[2] * i_other.m_mQuaternion[0] + m_mQuaternion[3] * i_other.m_mQuaternion[1];
	float D = m_mQuaternion[0] * i_other.m_mQuaternion[3] + m_mQuaternion[1] * i_other.m_mQuaternion[2] - m_mQuaternion[2] * i_other.m_mQuaternion[1] + m_mQuaternion[3] * i_other.m_mQuaternion[0];

	m_mQuaternion[0] = A;
	m_mQuaternion[1] = B;
	m_mQuaternion[2] = C;
	m_mQuaternion[3] = D;

	return *this;
}

PCEQuaternion PCEQuaternion::operator*(const PCEQuaternion& i_other) const
{
	PCEQuaternion oRes = *this;
	oRes += i_other;
	return oRes;
}

PCEQuaternion& PCEQuaternion::operator*=(float i_fScalar)
{
	m_mQuaternion[0] *= i_fScalar;
	m_mQuaternion[1] *= i_fScalar;
	m_mQuaternion[2] *= i_fScalar;
	m_mQuaternion[3] *= i_fScalar;

	return *this;
}

PCEQuaternion PCEQuaternion::operator*(float i_fScalar) const
{
	PCEQuaternion oRes = *this;
	oRes *= i_fScalar;
	return oRes;
}

PCEQuaternion& PCEQuaternion::operator/=(float i_fScalar)
{
	m_mQuaternion[0] /= i_fScalar;
	m_mQuaternion[1] /= i_fScalar;
	m_mQuaternion[2] /= i_fScalar;
	m_mQuaternion[3] /= i_fScalar;

	return *this;
}

PCEQuaternion PCEQuaternion::operator/(float i_fScalar) const
{
	PCEQuaternion oRes = *this;
	oRes /= i_fScalar;
	return oRes;
}

float& PCEQuaternion::operator[]( unsigned int i_uiIndex ) const
{
	return m_mQuaternion[i_uiIndex];
}

float PCEQuaternion::Module()
{
	return( sqrt((m_mQuaternion[0] * m_mQuaternion[0]) + (m_mQuaternion[1] * m_mQuaternion[1]) + (m_mQuaternion[2] * m_mQuaternion[2]) + (m_mQuaternion[3] * m_mQuaternion[3])) );
}

PCEQuaternion PCEQuaternion::Normal()
{
	float fModule = Module();
	PCEQuaternion oRes = *this;

	if(fModule > 0.000001f) {

		oRes /= fModule;
	}

	return oRes;
}
