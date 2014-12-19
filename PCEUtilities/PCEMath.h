#ifndef PCEMATH_H
#define PCEMATH_H

#include <cmath>
#include "PCEMatrix.h"
#include "PCEVector3.h"
#include "PCEMatrix3x3.h"
#include "PCEQuaternion.h"

#define M_PI acos(0)*2.0
#define M_PI_2 acos(0)
#define M_PI_4 acos(0)*0.5

PCEVector3D AbsoluteRotation(const PCEMatrix3x3& i_o3x3Matrix, const PCEVector3D& i_oVector3);

PCEVector3D RelativeRotation(const PCEMatrix3x3& i_o3x3Matrix, const PCEVector3D& i_oVector3);

double Module(const PCEVector3D& i_oVector3);

double Module( const PCEQuaternion& i_oQuaternion);

PCEVector3D Unit(const PCEVector3D& i_oVector3);

PCEQuaternion Unit(const PCEQuaternion& i_oQuaternion);

double DotProduct(const PCEVector3D& i_oFirst, const PCEVector3D& i_oSecond);

PCEVector3D WiseProduct(const PCEVector3D& i_oFirst, const PCEVector3D& i_oSecond);

PCEVector3D CrossProduct(const PCEVector3D& i_oFirst, const PCEVector3D& i_oSecond);

PCEMatrix3x3 MatriceDaQuaternione(const PCEQuaternion& i_oQuaternion);

PCEVector3D operator*( double i_fValue, const PCEVector3D& i_oSecond )
{
	PCEVector3D oRes = i_oSecond;
	oRes *= i_fValue;
	return oRes;
}

PCEVector3D operator/( double i_fValue, const PCEVector3D& i_oSecond )
{
	PCEVector3D oRes;

	oRes[0] = i_fValue / i_oSecond[0];
	oRes[1] = i_fValue / i_oSecond[1];
	oRes[2] = i_fValue / i_oSecond[2];

	return oRes;
}

template<unsigned int N>
double DotProduct( const PCEMatrix<N,1>& i_oFirst, const PCEMatrix<N,1>& i_oSecond )
{
	double fRes = 0;
	for (unsigned int uiIndex = 0; uiIndex < N; uiIndex++)
	{
		fRes += ( i_oFirst[uiIndex] * i_oSecond[uiIndex]);
	}

	return fRes;
}

template<unsigned int ROW, unsigned int COL>
PCEMatrix<ROW,COL> WiseProduct( const PCEMatrix<ROW,COL>& i_oFirst, const PCEMatrix<ROW,COL>& i_oSecond )
{
	PCEMatrix<ROW,COL> oRes;

	for ( unsigned int uiRow = 0; uiRow < ROW; ++uiRow )
	{
		for ( unsigned int uiCol = 0; uiCol < COL; ++uiCol )
		{
			oRes[uiRow][uiCol] = i_oFirst[uiRow][uiCol] * i_oSecond[uiRow][uiCol];
		}
	}

	return oRes;
}

template<unsigned int ROW, unsigned int COL>
PCEMatrix<ROW,COL> operator*( double i_fScalar, const PCEMatrix<ROW,COL>& i_oSecond )
{
	PCEMatrix<ROW,COL> oRes = i_oSecond;
	oRes *= i_fScalar;
	return oRes;
}

template<unsigned int ROW, unsigned int COL>
PCEMatrix<ROW,COL> operator/( double i_fScalar, const PCEMatrix<ROW,COL>& i_oSecond )
{
	PCEMatrix<ROW,COL> oRes;

	for ( unsigned int uiRow = 0; uiRow < ROW; ++uiRow )
	{
		for ( unsigned int uiCol = 0; uiCol < COL; ++uiCol )
		{
			oRes[uiRow][uiCol] = i_fScalar / i_oSecond[uiRow][uiCol];
		}
	}

	return oRes;
}

inline PCEVector3D operator*( const double& s, const PCEVector3D& v )
{
	return v * s;
}

#endif //PCEMATH_H
