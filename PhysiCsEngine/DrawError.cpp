#include "DrawError.h"
#include <stdio.h>

DrawError::DrawError(void)
{
}


DrawError::~DrawError(void)
{
}

void DrawError::StampError(PCE_ERROR i_error)
{
	char buffer[256];
	sprintf_s(buffer, "StampErrorCalled: ");
	switch (i_error)
	{
	case PCE_OK:
		sprintf_s(buffer, "OK");
		break;
	case PCE_CAPACITY:
		sprintf_s(buffer, "Error in capacity extension for subSpheres' array");
		break;
	case PCE_ADDSUBSPHERE:
		sprintf_s(buffer, "Error in calling calloc for add a subSphere in the array");
		break;
	default:
		sprintf_s(buffer, "Generic Error");
		break;
	}

	OutputDebugStringA(buffer);
}