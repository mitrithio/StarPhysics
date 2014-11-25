#include <assert.h>
#include "PCEString.h"

PCEString::PCEString()
	: mp_string(nullptr)
	, m_length(0)
{}

PCEString::PCEString( int i_iInteger, bool i_bValIsCapacity /*= false*/ )
{
	if ( i_bValIsCapacity )
	{
		mp_string = nullptr;
		m_length = i_iInteger;
	}
	else
	{
		if ( i_iInteger == 0 )
		{
			mp_string = "0";
			m_length = getSizeFromCharPtr( mp_string );
		}
		else
		{
			itoa( i_iInteger, mp_string, 10 );
			m_length = getSizeFromCharPtr( mp_string );
		}

	}
}

PCEString::PCEString(const char *io_string)
{
	m_length = getSizeFromCharPtr(io_string);
	
	mp_string = new char[m_length + 1];
	
	for (size_t i = 0; i < m_length; ++i)
	{
		mp_string[i] = io_string[i];
	}
	mp_string[m_length] = '\0';
}

PCEString::PCEString(const PCEString &i_other)
{
	m_length = i_other.m_length;
	mp_string = new char[m_length + 1];
	for (unsigned int i = 0; i < m_length; ++i)
	{
		mp_string[i] = i_other.mp_string[i];
	}
}

PCEString::~PCEString(void)
{
	if (mp_string != nullptr)
	{
		delete[] mp_string;
	}
}

const int PCEString::length() const
{
	return m_length;
}

char* PCEString::operator*()
{
	return mp_string;
}

char& PCEString::operator[](const int iValue) const
{
	return mp_string[iValue];
}

bool PCEString::operator==(const PCEString &rvalue) const
{
	bool equalFlag = (m_length == rvalue.m_length);

	for (size_t index = 0; equalFlag && index < m_length; ++index)
	{
		equalFlag = (mp_string[index] == rvalue[index]);
	}
	
	return equalFlag;
}

bool PCEString::operator!=(const PCEString &rvalue) const
{
	return !(*this == rvalue);
}

PCEString& PCEString::operator=(const PCEString &rvalue)
{
 	if (this != &rvalue)
	{
		m_length = rvalue.m_length;
		char *tmpString = mp_string;
		mp_string = (m_length == 0) ? nullptr : createSubStringFromCharPtr(rvalue.mp_string, m_length);
		delete [] tmpString;
	}

	return *this;
}

PCEString& PCEString::operator=(const char *rvalue)
{
	if (*this != rvalue)
	{
		m_length = getSizeFromCharPtr(rvalue);
		mp_string = (m_length == 0) ? nullptr : createSubStringFromCharPtr(rvalue, m_length);
	}
	return *this;
}

PCEString& PCEString::operator+=(const PCEString &rvalue)
{
	size_t totalStringSize = m_length;
	totalStringSize += rvalue.m_length;
	
	char *tmpString = new char[totalStringSize + 1];

	size_t indexOfThis = 0;
	for (; indexOfThis < m_length; ++indexOfThis)
	{
		tmpString[indexOfThis] = mp_string[indexOfThis];
	}
	for(size_t indexOfRvalue = 0; indexOfRvalue < rvalue.m_length; ++indexOfThis, ++indexOfRvalue)
	{
		tmpString[indexOfThis] = rvalue.mp_string[indexOfRvalue];
	}

	tmpString[totalStringSize] = '\0';
	delete[] mp_string;
	mp_string = tmpString;
	m_length = totalStringSize;
	return *this;
}

PCEString& PCEString::operator+=(const char *rvalue)
{
	PCEString tmpString(rvalue);
	return *this += tmpString;
}

const PCEString PCEString::operator+(const PCEString &rvalue) const
{
	PCEString tmp(*this);
	tmp += rvalue;
	return tmp;
}

const PCEString PCEString::operator+(const char *rvalue) const
{
	PCEString tmp(*this);
	tmp += rvalue;
	return tmp;
}

size_t PCEString::getSizeFromCharPtr(const char* i_charPtr) const
{
	if (i_charPtr == nullptr || i_charPtr == "")
	{
		return (size_t)0;
	}
	
	const char *tStr = i_charPtr;
	for (; *tStr != '\0'; ++tStr);

	return (tStr - i_charPtr);
}

char* PCEString::createSubStringFromCharPtr(const char* i_charPtr, size_t i_newLength)
{
	assert(i_charPtr != nullptr);
	
	delete[] mp_string;

	m_length = i_newLength;
	mp_string = new char[m_length + 1];

	for (size_t idx = 0; idx < m_length; ++idx)
	{
		mp_string[idx] = i_charPtr[idx];
	}

	mp_string[i_newLength] = '\0';
	return mp_string;
}

bool PCEString::operator==(const char *rvalue) const
{
	bool isEqual = (mp_string != nullptr && rvalue != nullptr);

	for (unsigned int i = 0; isEqual && mp_string[i] != '\0' && rvalue[i] != '\0'; ++i)
	{
		isEqual = (mp_string[i] == rvalue[i]);
	}

	return isEqual;
}

bool PCEString::operator!=(const char *rvalue) const
{
	return !(*this == rvalue);
}

const char* PCEString::c_str() const
{
	return mp_string;
}

PCEString PCEString::INT_TO_STRING( int i_int )
{
	if (i_int == 0)
		return "0";
	
	char tmp[sizeof(int)*8+1];
	_itoa_s( i_int%10, tmp, 10 );
	return tmp;
}

void PCEString::REVERT_STRING(PCEString* io_string)
{
	if( io_string != nullptr )
	{
		PCEString tmpString( io_string->length() );
		for( int i = 0; i < tmpString.length(); ++i )
		{
			tmpString[i] = (*io_string)[tmpString.length() - i];
		}
		*io_string = tmpString;
	}
}