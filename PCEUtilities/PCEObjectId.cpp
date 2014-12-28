#include "PCEObjectId.h"

PCEObjectId::PCEObjectId()
{
	m_ulHash = INVALID_OBJECT_ID.m_ulHash;
}

PCEObjectId::PCEObjectId( const PCEString& i_szString )
{
	m_ulHash = Djb2HashAlgorithm( i_szString.c_str() );
#ifdef _DEBUG
	m_szDebugName = i_szString;
#endif
}

PCEObjectId::PCEObjectId( const PCEObjectId& i_other )
{
	m_ulHash = i_other.m_ulHash;
#ifdef _DEBUG
	m_szDebugName = i_other.m_szDebugName;
#endif
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

unsigned long PCEObjectId::GetHash() const
{
	return m_ulHash;
}

PCEObjectId& PCEObjectId::operator=( const PCEObjectId& i_other )
{
	if ( this != &i_other )
	{
		m_ulHash = i_other.m_ulHash;
#ifdef _DEBUG
		m_szDebugName = i_other.m_szDebugName;
#endif
	}

	return *this;
}

bool operator==( const PCEObjectId& i_first, const PCEObjectId& i_second )
{
	return i_first.GetHash() == i_second.GetHash();
}

bool operator!=( const PCEObjectId& i_first, const PCEObjectId& i_second )
{
	return !(i_first.GetHash() == i_second.GetHash());
}

bool operator<( const PCEObjectId& i_first, const PCEObjectId& i_second )
{
	return i_first.GetHash() < i_second.GetHash();
}

bool operator<=( const PCEObjectId& i_first, const PCEObjectId& i_second )
{
	return !(i_second.GetHash() < i_first.GetHash());
}

bool operator>( const PCEObjectId& i_first, const PCEObjectId& i_second )
{
	return i_second.GetHash() < i_first.GetHash();
}

bool operator>=( const PCEObjectId& i_first, const PCEObjectId& i_second )
{
	return !(i_first.GetHash() < i_second.GetHash());
}
