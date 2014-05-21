#include "PCEString.h"

PCEString::PCEString():
	  mpString(nullptr)
	, length(0)
{}

PCEString::PCEString(const char *io_string)
{
	length = getSizeFromCharPtr(io_string);
	
	mpString = new char[length + 1];
	
	for (size_t i = 0; i < length; ++i)
	{
		mpString[i] = io_string[i];
	}
	mpString[length] = '\0';
}


PCEString::~PCEString(void)
{
	if (mpString != nullptr && length != 0)
	{
		delete[] mpString;
	}
}

const size_t PCEString::size() const
{
	return length;
}

char* PCEString::operator*()
{
	return mpString;
}

char& PCEString::operator[](const int iValue) const
{
	return mpString[iValue];
}

bool PCEString::operator==(const PCEString &rvalue)
{
	bool equalFlag = true;
	
	if (length != rvalue.length)
	{
		equalFlag = false;
	}

	int i = 0;
	for (; i < length && equalFlag; ++i)
	{
		if (mpString[i] != rvalue[i])
		{
			equalFlag = false;
		}
	}
	/*if (mpString[i] != rvalue[i] && mpString != '\0')
	{
		equalFlag = false;
	}*/
	return equalFlag;
}

bool PCEString::operator!=(const PCEString &rvalue)
{
	return !(*this == rvalue);
}

PCEString& PCEString::operator=(const PCEString &rvalue)
{
 	/*if (length == 0)
 	{
 		mpString = new char[rvalue.size()];
 	}
 	else if (length != rvalue.size())
	{
		delete[] mpString;
		mpString = new char[rvalue.size()];
	}

	for (int i = 0; rvalue[i] != '\0'; ++i)
	{
		mpString[i] = rvalue[i];
	}*/

	length = rvalue.length;
	mpString = (length == 0) ? nullptr : createStringFromCharPtr(rvalue.mpString, length);

	return *this;
}

PCEString& PCEString::operator=(const char *rvalue)
{
	length = getSizeFromCharPtr(rvalue);
	
	mpString = (length == 0) ? nullptr : createStringFromCharPtr(rvalue, length);

	return *this;
}

PCEString& PCEString::operator+=(const PCEString &rvalue)
{
	size_t totalStringSize = length;
	totalStringSize += rvalue.length;
	
	char *tmpString = new char[totalStringSize + 1];

	int i = 0;
	for (; i < length; ++i)
	{
		tmpString[i] = mpString[i];
	}
	//--i;
	for(int j = 0; j < rvalue.length; ++i, ++j)
	{
		tmpString[i] = rvalue.mpString[j];
	}

	tmpString[totalStringSize] = '\0';
	delete[] mpString;
	mpString = tmpString;
	length = totalStringSize;
	return *this;
}

PCEString& PCEString::operator+=(const char *rvalue)
{
	PCEString tmpString(rvalue);
	return *this += tmpString;
}

PCEString& PCEString::operator+(const PCEString &rvalue)
{
	*this += rvalue;
	return *this;
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

char* PCEString::createStringFromCharPtr(const char* i_charPtr, size_t i_newLength)
{
	if (mpString == nullptr)
	{
		mpString = new char[i_newLength + 1];
	}
	else
	{
		delete[] mpString;
		mpString = new char[i_newLength + 1];
	}

	for (int i = 0; i < length; ++i)
	{
		mpString[i] = i_charPtr[i];
	}

	mpString[i_newLength] = '\0';
	return mpString;
}