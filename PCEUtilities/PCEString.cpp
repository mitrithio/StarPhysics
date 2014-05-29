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

PCEString::PCEString(const PCEString &i_other)
{
	length = i_other.length;
	mpString = new char[length + 1];
	for (unsigned int i = 0; i < length; ++i)
	{
		mpString[i] = i_other.mpString[i];
	}
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
 	if (*this != rvalue)
	{
		length = rvalue.length;
		mpString = (length == 0) ? nullptr : createStringFromCharPtr(rvalue.mpString, length);
	}

	return *this;
}

PCEString& PCEString::operator=(const char *rvalue)
{
	if (*this != rvalue)
	{
		length = getSizeFromCharPtr(rvalue);
		mpString = (length == 0) ? nullptr : createStringFromCharPtr(rvalue, length);
	}
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

char* PCEString::createStringFromCharPtr(const char* i_charPtr, size_t i_newLength)
{
	if (i_charPtr == nullptr)
	{
		return nullptr;
	}


	if (mpString != nullptr)
	{
		delete[] mpString;
	}

	length = i_newLength;
	mpString = new char[length + 1];

	for (int i = 0; i < length; ++i)
	{
		mpString[i] = i_charPtr[i];
	}

	mpString[i_newLength] = '\0';
	return mpString;
}

bool PCEString::operator==(const char *rvalue)
{
	bool isEqual = (mpString != nullptr && rvalue != nullptr);

	for (unsigned int i = 0; isEqual && mpString[i] != '\0' && rvalue[i] != '\0'; ++i)
	{
		isEqual = (mpString[i] == rvalue[i]);
	}

	return isEqual;
}
bool PCEString::operator!=(const char *rvalue)
{
	return !(*this == rvalue);
}
