#ifndef PCEMATH_H
#define PCEMATH_H

#include <math.h>
#include "PCEPoint.h"
#include "PCEVector3.h"
#include "PCEMatrix.h"
#include "PCEQuaternion.h"

PCEHVector3 AbsoluteRotation(const PCEMatrix<3,3>& i_o3x3Matrix, const PCEHVector3& i_oVector3);

PCEHVector3 RelativeRotation(const PCEMatrix<3,3>& i_o3x3Matrix, const PCEHVector3& i_oVector3);

float Module(const PCEHVector3& i_oVector3);

float Module( const PCEQuaternion& i_oQuaternion);

PCEHVector3 Normal(const PCEHVector3& i_oVector3);

PCEQuaternion Normal( const PCEQuaternion& i_oQuaternion);

PCEHVector3 CrossProduct( const PCEHVector3& i_oFirst, const PCEHVector3& i_oSecond );

PCEMatrix<3,3> MatriceDaQuaternione(const PCEQuaternion& i_oQuaternion);


#endif //PCEMATH_H