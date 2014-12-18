#ifndef PCEMATH_H
#define PCEMATH_H

#include <cmath>
#include "PCEPoint.h"
#include "PCEVector3.h"
#include "PCEMatrix.h"
#include "PCEQuaternion.h"

#define M_PI acos(0)*2.0
#define M_PI_2 acos(0)
#define M_PI_4 acos(0)*0.5

PCEHVector3 AbsoluteRotation(const PCEMatrix<3,3>& i_o3x3Matrix, const PCEHVector3& i_oVector3);

PCEHVector3 RelativeRotation(const PCEMatrix<3,3>& i_o3x3Matrix, const PCEHVector3& i_oVector3);

double Module(const PCEHVector3& i_oVector3);

double Module( const PCEQuaternion& i_oQuaternion);

PCEHVector3 Normal(const PCEHVector3& i_oVector3);

PCEQuaternion Normal(const PCEQuaternion& i_oQuaternion);

double DotProduct(const PCEHVector3& i_oFirst, const PCEHVector3& i_oSecond);

PCEHVector3 WiseProduct(const PCEHVector3& i_oFirst, const PCEHVector3& i_oSecond);

PCEHVector3 CrossProduct(const PCEHVector3& i_oFirst, const PCEHVector3& i_oSecond);

PCEMatrix<3,3> MatriceDaQuaternione(const PCEQuaternion& i_oQuaternion);

PCEHVector3 operator*( double i_fScalar, const PCEHVector3& i_oSecond )
{
	PCEHVector3 oRes = i_oSecond;
	oRes *= i_fScalar;
	return oRes;
}

PCEHVector3 operator/( double i_fScalar, const PCEHVector3& i_oSecond )
{
	PCEHVector3 oRes;

	oRes[0] = i_fScalar / i_oSecond[0];
	oRes[1] = i_fScalar / i_oSecond[1];
	oRes[2] = i_fScalar / i_oSecond[2];

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

#endif //PCEMATH_H
