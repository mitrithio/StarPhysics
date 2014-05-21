#include "WinDrawSystemApi.h"
#include "TGAFile.h"

bool TGAFile::load(const char* fileName)
{
	DWORD dw; 
	HANDLE hFile = CreateFileA(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 
	if(hFile == INVALID_HANDLE_VALUE)
	{
		OutputDebugStringA("File \""); 
		OutputDebugStringA(fileName); 
		OutputDebugStringA("\" can't be opened.\n"); 
		return false; 
	}
	ReadFile(hFile, &Header, sizeof(TgaHeader), &dw, NULL);
	size_t sz = Header.width * Header.height; 
	RawData = new TgaColorData[sz]; 
	SetFilePointer(hFile, Header.idlength, NULL, FILE_CURRENT); 	
	if(Header.bitsperpixel == 32) 
		ReadFile(hFile, RawData, sizeof(TgaColorData) * sz, &dw, NULL);
	else if(Header.bitsperpixel == 24) 
	{
		size_t bytesRequired = sz * 3; 
		unsigned char* buffer = new unsigned char[bytesRequired]; 
		ReadFile(hFile, buffer, bytesRequired, &dw, NULL);
		unsigned char* cursor = buffer; 
		for(size_t i=0; i<sz; i++) 
		{
			RawData[i].BgraInfoData.b = cursor[0]; 
			RawData[i].BgraInfoData.g = cursor[1]; 
			RawData[i].BgraInfoData.r = cursor[2]; 
			RawData[i].BgraInfoData.a = 255; 
			cursor+=3; 
		}
		delete[] buffer; 
	}

	CloseHandle(hFile); 
	return true; 
}