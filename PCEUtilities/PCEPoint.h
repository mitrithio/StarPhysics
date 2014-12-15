#ifndef PCEPOINT_H
#define PCEPOINT_H

#include "PCEMatrix.h"
#include <float.h>

typedef PCEMatrix<3,1> PCEPoint;

static const float FLOAT_ARRAY_MAX[3] = {FLT_MAX, FLT_MAX, FLT_MAX};
static const PCEPoint INVALID_POINT( FLOAT_ARRAY_MAX, 3);
#endif // PCEPOINT_H