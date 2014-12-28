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
	
	unsigned long GetHash() const;

	PCEObjectId& operator=( const PCEObjectId& i_other );

private:

	unsigned long m_ulHash;
#ifdef _DEBUG
	PCEString m_szDebugName;
#endif
};

bool operator==(const PCEObjectId& i_first, const PCEObjectId& i_second);
bool operator!=(const PCEObjectId& i_first, const PCEObjectId& i_second);
bool operator<(const PCEObjectId& i_first, const PCEObjectId& i_second);
bool operator<=(const PCEObjectId& i_first, const PCEObjectId& i_second);
bool operator>(const PCEObjectId& i_first, const PCEObjectId& i_second);
bool operator>=(const PCEObjectId& i_first, const PCEObjectId& i_second);

static PCEObjectId INVALID_OBJECT_ID("");

#endif//PCEOBJECTID_H