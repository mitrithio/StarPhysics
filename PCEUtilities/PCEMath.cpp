#include "PCEMath.h"

PCEHVector3 AbsoluteRotation( const PCEMatrix<3,3>& i_o3x3Matrix, const PCEHVector3& i_oVector3 )
{
	PCEHVector3 oRes;

	float X = i_oVector3[0];
	float Y = i_oVector3[1];
	float Z = i_oVector3[2];

	oRes[0] = i_o3x3Matrix[0][0] * X + i_o3x3Matrix[1][0] * Y + i_o3x3Matrix[2][0] * Z;
	oRes[1] = i_o3x3Matrix[0][1] * X + i_o3x3Matrix[1][1] * Y + i_o3x3Matrix[2][1] * Z;
	oRes[2] = i_o3x3Matrix[0][2] * X + i_o3x3Matrix[1][2] * Y + i_o3x3Matrix[2][2] * Z;

	return oRes;
}

PCEHVector3 RelativeRotation( const PCEMatrix<3,3>& i_o3x3Matrix, const PCEHVector3& i_oVector3 )
{
	PCEHVector3 oRes;

	float X = i_oVector3[0];
	float Y = i_oVector3[1];
	float Z = i_oVector3[2];

	oRes[0] = i_o3x3Matrix[0][0] * X + i_o3x3Matrix[0][1] * Y + i_o3x3Matrix[0][2] * Z;
	oRes[1] = i_o3x3Matrix[1][0] * X + i_o3x3Matrix[1][1] * Y + i_o3x3Matrix[1][2] * Z;
	oRes[2] = i_o3x3Matrix[2][0] * X + i_o3x3Matrix[2][1] * Y + i_o3x3Matrix[2][2] * Z;

	return oRes;
}

float Module( const PCEMatrix<3,1>& i_oVector3 )
{
	return( sqrt((i_oVector3[0] * i_oVector3[0]) + (i_oVector3[1] * i_oVector3[1]) + (i_oVector3[2] * i_oVector3[2])) );
}

PCEHVector3 Normal( const PCEHVector3& i_oVector3 )
{
	float fModule = Module( i_oVector3 );
	PCEHVector3 oVector = i_oVector3;

	if(fModule > 0.000001f)
	{
		oVector[0] /= fModule;
		oVector[1] /= fModule;
		oVector[2] /= fModule;
	}

	return oVector;
}

PCEHVector3 CrossProduct( const PCEHVector3& i_oFirst, const PCEHVector3& i_oSecond )
{
	PCEHVector3 oThird;

	oThird[0] = ( i_oFirst[1] * i_oSecond[2] ) - ( i_oFirst[2] * i_oSecond[1] );
	oThird[1] = ( i_oFirst[2] * i_oSecond[0] ) - ( i_oFirst[0] * i_oSecond[2] );
	oThird[2] = ( i_oFirst[0] * i_oSecond[1] ) - ( i_oFirst[1] * i_oSecond[0] );

	return oThird;
}

PCEMatrix<3,3> MatriceDaQuaternione( const PCEQuaternion& i_oQuaternion )
{
	float X2 = i_oQuaternion[1] * i_oQuaternion[1];
	float Y2 = i_oQuaternion[2] * i_oQuaternion[2];
	float Z2 = i_oQuaternion[3] * i_oQuaternion[3];
	float XY = i_oQuaternion[1] * i_oQuaternion[2];
	float XZ = i_oQuaternion[1] * i_oQuaternion[3];
	float YZ = i_oQuaternion[2] * i_oQuaternion[3];
	float SX = i_oQuaternion[0] * i_oQuaternion[1];
	float SY = i_oQuaternion[0] * i_oQuaternion[2];
	float SZ = i_oQuaternion[0] * i_oQuaternion[3];

	PCEMatrix<3,3> oRes;

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