#ifndef PCESTRING_H
#define PCESTRING_H

#include "PCEUtilitiesSystemApi.h"

class PCEString
{
public:

	PCEString();
	PCEString(int capacity);
	PCEString(const char* io_string);
	PCEString(const PCEString &i_other);
	PCEString(int i_int);

	~PCEString();

	const int size() const;
	const char* getStringAsChar() const;

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

	static PCEString intToString(const int i_int);
	static void revertString(PCEString* io_string);

private:
	char *mp_string;
	size_t m_length;
	PCEString& operator-(const PCEString &rvalue){return *this;};
	PCEString& operator-=(const PCEString &rvalue){return *this;};
	size_t getSizeFromCharPtr(const char* i_charPtr) const;
	char* createSubStringFromCharPtr(const char* i_charPtr, size_t i_newLength);
};

#endif