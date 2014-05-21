#ifndef TGAFILE_H
#define TGAFILE_H

//utility class for reading .tga files. 

#ifndef NULL
#define NULL 0L
#endif

class TGAFile
{
public: 
	typedef unsigned char TgaByte; 
	typedef unsigned __int32 TgaColor; 
#pragma pack(push, 1)
	struct TgaHeader
	{
		char  idlength;
		char  colourmaptype;
		char  datatypecode;
		short colourmaporigin;
		short colourmaplength;
		char  colourmapdepth;
		short x_origin;
		short y_origin;
		short width;
		short height;
		char  bitsperpixel;
		char  imagedescriptor;		
	} Header; 
	union TgaColorData
	{
		struct RgbaInfo
		{
			TgaByte b; 
			TgaByte g; 
			TgaByte r; 
			TgaByte a; 
		} BgraInfoData; 
		TgaColor Color; 
	}; 
	TgaColorData* RawData; 
#pragma pack(pop)
protected: 

public: 
	TGAFile(): RawData(NULL){} 
	~TGAFile(){ if(RawData != NULL ) delete[] RawData;  } 
	bool load(const char* fileName); 
}; 

#endif