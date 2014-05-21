#ifndef PCE_DRAWERROR_H
#define	PCE_DRAWERROR_H

#include "PCESystemApi.h"
#include "ErrorDefinitions.h"

class DrawError
{
public:
	DrawError(void);
	~DrawError(void);

	static void StampError(PCE_ERROR i_error);
};

#endif