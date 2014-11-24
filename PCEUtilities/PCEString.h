#ifndef PCESTRING_H
#define PCESTRING_H

#include "PCEUtilitiesSystemApi.h"

class PCEString
{
public:

	PCEString();
	PCEString(int i_iInteger, bool i_bValIsCapacity = false);
	PCEString(const char* io_string);
	PCEString(const PCEString &i_other);

	~PCEString();

	const int length() const;
	const char* c_str() const;

	char* operator*(void);
	char& operator[](const int iValue) const;
	bool operator==(const PCEString &rvalue);
	bool operator!=(const PCEString &rvalue);
	bool operator==(const char *rvalue);
	bool operator!=(const char *rvalue);
	PCEString& operator=(const PCEString &rvalue);
	PCEString& operator=(const char *rvalue);
	PCEString& operator+=(const PCEString &rvalue);
	PCEString& operator+=(const char *rvalue);
	const PCEString operator+(const PCEString &rvalue) const;
	const PCEString operator+(const char *rvalue) const;

	static PCEString INT_TO_STRING( int i_int);
	static void REVERT_STRING(PCEString* io_string);

private:
	char *mp_string;
	size_t m_length;
	PCEString& operator-(const PCEString &rvalue);
	PCEString& operator-=(const PCEString &rvalue);
	size_t getSizeFromCharPtr(const char* i_charPtr) const;
	char* createSubStringFromCharPtr(const char* i_charPtr, size_t i_newLength);
};

#endif