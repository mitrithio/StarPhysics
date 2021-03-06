#include "PCEMath.h"

PCEVector3D AbsoluteRotation( const PCEMatrix3x3& i_o3x3Matrix, const PCEVector3D& i_oVector3 )
{
	PCEVector3D oRes;

	double X = i_oVector3[0];
	double Y = i_oVector3[1];
	double Z = i_oVector3[2];

	oRes[0] = i_o3x3Matrix[0][0] * X + i_o3x3Matrix[1][0] * Y + i_o3x3Matrix[2][0] * Z;
	oRes[1] = i_o3x3Matrix[0][1] * X + i_o3x3Matrix[1][1] * Y + i_o3x3Matrix[2][1] * Z;
	oRes[2] = i_o3x3Matrix[0][2] * X + i_o3x3Matrix[1][2] * Y + i_o3x3Matrix[2][2] * Z;

	return oRes;
}

PCEVector3D RelativeRotation( const PCEMatrix3x3& i_o3x3Matrix, const PCEVector3D& i_oVector3 )
{
	PCEVector3D oRes;

	double X = i_oVector3[0];
	double Y = i_oVector3[1];
	double Z = i_oVector3[2];

	oRes[0] = i_o3x3Matrix[0][0] * X + i_o3x3Matrix[0][1] * Y + i_o3x3Matrix[0][2] * Z;
	oRes[1] = i_o3x3Matrix[1][0] * X + i_o3x3Matrix[1][1] * Y + i_o3x3Matrix[1][2] * Z;
	oRes[2] = i_o3x3Matrix[2][0] * X + i_o3x3Matrix[2][1] * Y + i_o3x3Matrix[2][2] * Z;

	return oRes;
}

double Module( const PCEVector3D& i_oVector3 )
{
	return( sqrt((i_oVector3[0] * i_oVector3[0]) + (i_oVector3[1] * i_oVector3[1]) + (i_oVector3[2] * i_oVector3[2])) );
}

PCEVector3D Unit( const PCEVector3D& i_oVector3 )
{
	double fModule = Module( i_oVector3 );
	PCEVector3D oVector = i_oVector3;

	if(fModule > 0.000001f)
	{
		oVector[0] /= fModule;
		oVector[1] /= fModule;
		oVector[2] /= fModule;
	}

	return oVector;
}

double DotProduct( const PCEVector3D& i_oFirst, const PCEVector3D& i_oSecond )
{
	return ( i_oFirst[0] * i_oSecond[0] ) + (i_oFirst[1]*i_oSecond[1]) + (i_oFirst[2]*i_oSecond[2]);
}

PCEVector3D CrossProduct( const PCEVector3D& i_oFirst, const PCEVector3D& i_oSecond )
{
	PCEVector3D oThird;

	oThird[0] = ( i_oFirst[1] * i_oSecond[2] ) - ( i_oFirst[2] * i_oSecond[1] );
	oThird[1] = ( i_oFirst[2] * i_oSecond[0] ) - ( i_oFirst[0] * i_oSecond[2] );
	oThird[2] = ( i_oFirst[0] * i_oSecond[1] ) - ( i_oFirst[1] * i_oSecond[0] );

	return oThird;
}

PCEMatrix3x3 MatriceDaQuaternione( const PCEQuaternion& i_oQuaternion )
{
	double X2 = i_oQuaternion[1] * i_oQuaternion[1];
	double Y2 = i_oQuaternion[2] * i_oQuaternion[2];
	double Z2 = i_oQuaternion[3] * i_oQuaternion[3];
	double XY = i_oQuaternion[1] * i_oQuaternion[2];
	double XZ = i_oQuaternion[1] * i_oQuaternion[3];
	double YZ = i_oQuaternion[2] * i_oQuaternion[3];
	double SX = i_oQuaternion[0] * i_oQuaternion[1];
	double SY = i_oQuaternion[0] * i_oQuaternion[2];
	double SZ = i_oQuaternion[0] * i_oQuaternion[3];

	PCEMatrix3x3 oRes;

	oRes[0][0] = 1.0f - 2.0f * (Y2 + Z2);
	oRes[0][1] = 2.0f * (XY + SZ);
	oRes[0][2] = 2.0f * (XZ - SY);
	oRes[1][0] = 2.0f * (XY - SZ);
	oRes[1][1] = 1.0f - 2.0f * (Z2 + X2);
	oRes[1][2] = 2.0f * (YZ + SX);
	oRes[2][0] = 2.0f * (XZ + SY);
	oRes[2][1] = 2.0f * (YZ - SX);
	oRes[2][2] = 1.0f - 2.0f * (X2 + Y2);

	return oRes;
}

PCEVector3D WiseProduct( const PCEVector3D& i_oFirst, const PCEVector3D& i_oSecond )
{
	PCEVector3D oRes;

	oRes[0] = i_oFirst[0] * i_oSecond[0];
	oRes[1] = i_oFirst[1] * i_oSecond[1];
	oRes[2] = i_oFirst[2] * i_oSecond[2];

	return oRes;
}
