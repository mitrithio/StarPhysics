#include "PCEObjectId.h"

PCEObjectId::PCEObjectId()
{
	m_ulHash = INVALID_OBJECT_ID.m_ulHash;
}

PCEObjectId::PCEObjectId( const PCEString& i_szString )
{
	m_ulHash = Djb2HashAlgorithm( i_szString.c_str() );
}

PCEObjectId::PCEObjectId( const PCEObjectId& i_other )
{
	m_ulHash = i_other.m_ulHash;
}

unsigned long PCEObjectId::Djb2HashAlgorithm( const char* str )
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++) 
	{
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}

bool PCEObjectId::operator==( const PCEObjectId& i_other ) const
{
	return m_ulHash == i_other.m_ulHash;
}

bool PCEObjectId::operator!=( const PCEObjectId& i_other ) const
{
	return ( *this == i_other );
}

PCEObjectId& PCEObjectId::operator=( const PCEObjectId& i_other )
{
	if ( this != &i_other )
	{
		m_ulHash = i_other.m_ulHash;
	}

	return *this;
}
