#ifndef PCESTRING_H
#define PCESTRING_H

#include "PCEUtilitiesSystemApi.h"

class PCEString
{
private:
	char *mpString;
	size_t length;
	PCEString& operator-(const PCEString &rvalue){return *this;};
	PCEString& operator-=(const PCEString &rvalue){return *this;};
	size_t getSizeFromCharPtr(const char* i_charPtr) const;
	char* createStringFromCharPtr(const char* i_charPtr, size_t i_newLength);
public:
	PCEString();
	PCEString(const char* io_string);

	~PCEString();

	const size_t size() const;

	char* operator*(void);
	char& operator[](const int iValue) const;
	bool operator==(const PCEString &rvalue);
	bool operator!=(const PCEString &rvalue);
	PCEString& operator=(const PCEString &rvalue);
	PCEString& operator=(const char *rvalue);
	PCEString& operator+=(const PCEString &rvalue);
	PCEString& operator+=(const char *rvalue);
	PCEString& operator+(const PCEString &rvalue);

};

#endif