#include "PCEQuaternion.h"
#include "PCEMath.h"

PCEQuaternion::PCEQuaternion()
{
	m_mQuaternion = new double[4]();
	m_mQuaternion[0] = 0.0f;
	m_mQuaternion[1] = 0.0f;
	m_mQuaternion[2] = 0.0f;
	m_mQuaternion[3] = 0.0f;
}

PCEQuaternion::PCEQuaternion( double a, double b, double c, double d )
{
	m_mQuaternion = new double[4]();
	m_mQuaternion[0] = a;
	m_mQuaternion[1] = b;
	m_mQuaternion[2] = c;
	m_mQuaternion[3] = d;
}

PCEQuaternion::PCEQuaternion( const PCEQuaternion& i_other )
{
	m_mQuaternion = new double[4]();
	m_mQuaternion[0] = i_other.m_mQuaternion[0];
	m_mQuaternion[1] = i_other.m_mQuaternion[1];
	m_mQuaternion[2] = i_other.m_mQuaternion[2];
	m_mQuaternion[3] = i_other.m_mQuaternion[3];
}

PCEQuaternion::PCEQuaternion( const PCEHVector3& i_vEulerAngles )
{
	double c1 = cos(i_vEulerAngles[2U] * 0.5f);
	double c2 = cos(i_vEulerAngles[1U] * 0.5f);
	double c3 = cos(i_vEulerAngles[0U] * 0.5f);
	double s1 = sin(i_vEulerAngles[2U] * 0.5f);
	double s2 = sin(i_vEulerAngles[1U] * 0.5f);
	double s3 = sin(i_vEulerAngles[0U] * 0.5f);

	m_mQuaternion[0] = c1*c2*s3 - s1*s2*c3;
	m_mQuaternion[1] = c1*s2*c3 + s1*c2*s3;
	m_mQuaternion[2] = s1*c2*c3 - c1*s2*s3;
	m_mQuaternion[3] = c1*c2*c3 + s1*s2*s3;
}

PCEQuaternion::PCEQuaternion( const double* i_fDimensions )
{
	m_mQuaternion = new double[4]();
	m_mQuaternion[0] = i_fDimensions[0];
	m_mQuaternion[1] = i_fDimensions[1];
	m_mQuaternion[2] = i_fDimensions[2];
	m_mQuaternion[3] = i_fDimensions[3];
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
	double A = m_mQuaternion[0] * i_other.m_mQuaternion[0] - m_mQuaternion[1] * i_other.m_mQuaternion[1] - m_mQuaternion[2] * i_other.m_mQuaternion[2] - m_mQuaternion[3] * i_other.m_mQuaternion[3];
	double B = m_mQuaternion[0] * i_other.m_mQuaternion[1] + m_mQuaternion[1] * i_other.m_mQuaternion[0] + m_mQuaternion[2] * i_other.m_mQuaternion[3] - m_mQuaternion[3] * i_other.m_mQuaternion[2];
	double C = m_mQuaternion[0] * i_other.m_mQuaternion[2] - m_mQuaternion[1] * i_other.m_mQuaternion[3] + m_mQuaternion[2] * i_other.m_mQuaternion[0] + m_mQuaternion[3] * i_other.m_mQuaternion[1];
	double D = m_mQuaternion[0] * i_other.m_mQuaternion[3] + m_mQuaternion[1] * i_other.m_mQuaternion[2] - m_mQuaternion[2] * i_other.m_mQuaternion[1] + m_mQuaternion[3] * i_other.m_mQuaternion[0];

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

PCEQuaternion& PCEQuaternion::operator*=(double i_fScalar)
{
	m_mQuaternion[0] *= i_fScalar;
	m_mQuaternion[1] *= i_fScalar;
	m_mQuaternion[2] *= i_fScalar;
	m_mQuaternion[3] *= i_fScalar;

	return *this;
}

PCEQuaternion PCEQuaternion::operator*(double i_fScalar) const
{
	PCEQuaternion oRes = *this;
	oRes *= i_fScalar;
	return oRes;
}

PCEQuaternion& PCEQuaternion::operator/=(double i_fScalar)
{
	m_mQuaternion[0] /= i_fScalar;
	m_mQuaternion[1] /= i_fScalar;
	m_mQuaternion[2] /= i_fScalar;
	m_mQuaternion[3] /= i_fScalar;

	return *this;
}

PCEQuaternion PCEQuaternion::operator/(double i_fScalar) const
{
	PCEQuaternion oRes = *this;
	oRes /= i_fScalar;
	return oRes;
}

double& PCEQuaternion::operator[]( unsigned int i_uiIndex ) const
{
	return m_mQuaternion[i_uiIndex];
}

double PCEQuaternion::Module()
{
	return( sqrt((m_mQuaternion[0] * m_mQuaternion[0]) + (m_mQuaternion[1] * m_mQuaternion[1]) + (m_mQuaternion[2] * m_mQuaternion[2]) + (m_mQuaternion[3] * m_mQuaternion[3])) );
}

PCEQuaternion PCEQuaternion::Normal()
{
	double fModule = Module();
	PCEQuaternion oRes = *this;

	if(fModule > 0.000001f) {

		oRes /= fModule;
	}

	return oRes;
}

// this function is replicated from Stanford University quaternion class.
PCEHVector3 PCEQuaternion::EulerAngle()
{
	PCEHVector3 vEulerAngles;
	const static double HALF_PI = M_PI_2;
	const static double EPSILON = 1e-10;
	double sqw, sqx, sqy, sqz;

	sqw = pow(m_mQuaternion[3],2);
	sqx = pow(m_mQuaternion[0],2);
	sqy = pow(m_mQuaternion[1],2);
	sqz = pow(m_mQuaternion[2],2);

	vEulerAngles[1] = asin(2.0 * (m_mQuaternion[3]*m_mQuaternion[1] - m_mQuaternion[0]*m_mQuaternion[2]));
	if (HALF_PI - fabs(vEulerAngles[1]) > EPSILON) 
	{
		vEulerAngles[2] = atan2(2.0 * (m_mQuaternion[0]*m_mQuaternion[1] + m_mQuaternion[3]*m_mQuaternion[2]),	sqx - sqy - sqz + sqw);
		vEulerAngles[0] = atan2(2.0 * (m_mQuaternion[3]*m_mQuaternion[0] + m_mQuaternion[1]*m_mQuaternion[2]),	sqw - sqx - sqy + sqz);
	} 
	else 
	{
		vEulerAngles[2] = atan2(2*m_mQuaternion[1]*m_mQuaternion[2] - 2*m_mQuaternion[0]*m_mQuaternion[3], 2*m_mQuaternion[0]*m_mQuaternion[2] + 2*m_mQuaternion[1]*m_mQuaternion[3]);
		vEulerAngles[0] = 0.0;

		if (vEulerAngles[1] < 0)
		{
			vEulerAngles[2] = M_PI - vEulerAngles[2];
		}
	}
	return vEulerAngles;
}
