#ifndef PCEPOINT_H
#define PCEPOINT_H

#include "PCEMatrix.h"
#include <float.h>

typedef PCEMatrix<3,1> PCEPoint;

static const double FLOAT_ARRAY_MAX[3] = {DBL_MAX, DBL_MAX, DBL_MAX};
static const PCEPoint INVALID_POINT( FLOAT_ARRAY_MAX, 3);
#endif // PCEPOINT_H