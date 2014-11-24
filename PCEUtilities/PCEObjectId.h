#ifndef PCEOBJECTID_H
#define PCEOBJECTID_H

#include "PCEString.h"

class PCEObjectId
{
public:

	PCEObjectId();
	PCEObjectId( const PCEString& i_szString );
	PCEObjectId( const PCEObjectId& i_other );

	static unsigned long Djb2HashAlgorithm( const char* str );

	bool operator==( const PCEObjectId& i_other );
	bool operator!=( const PCEObjectId& i_other );
	PCEObjectId& operator=( const PCEObjectId& i_other );

private:

	unsigned long m_ulHash;
};

static PCEObjectId INVALID_OBJECT_ID("");

#endif//PCEOBJECTID_H