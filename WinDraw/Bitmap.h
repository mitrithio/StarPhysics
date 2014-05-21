#ifndef BITMAP_H
#define BITMAP_H

#include "WinDrawSystemApi.h"

class TGAFile; 
//why double forward declaration? O.o [EP]
class TGAFile; 

class Font;

class Bitmap
{
protected: 
	bool requiresDeletion; 
	HDC hdc; 
	void* pixelData; 
	int width; 
	int height; 

	void Create(int w, int h, TGAFile* pixelData); 
	void Setup(); 
	Bitmap(const Bitmap&) {/* bitmaps cannot be copied*/}
public: 
	Bitmap(int w, int h); //creates an empty bitmap. 
	Bitmap(HDC drawingDC, int w, int h); //creates a bitmap for drawing on the main window
	Bitmap(TGAFile* file); //creates a bitmap from a TGA file
	Bitmap(const char* fileName); //creates a bitmap from a TGA file 
	~Bitmap(); 

	int GetWidth(){ return width; }			
	int GetHeight() { return height; } 

	void CopyTo(Bitmap* other, int x, int y); 

	void DrawTo(Bitmap* other, int x, int y); //draws this bitmap at (x, y) on "other" with alpha blending 
	void DrawRectTo(Bitmap* other, int destx, int desty, int srcx, int srcy, int w, int h); //draws a rectangle (w x h) of this bitmap at (srcx, srcy) on "other" at (srcx, srcy) with alpha blending 

	//draws this bitmap on "other" with alpha blending 
	//rotating it of (radAngle) radians around an arbitrary pivot lying in (pivotX, pivoty, in bitmap coordinates), placing it in (srcx, srcy)
	void DrawRotatedTo(Bitmap* other, int destx, int desty, int pivotx, int pivoty, float radAngle); 

	//draws a portion (w x h) of this bitmap at (srcx, srcy) on "other" with alpha blending 
	//rotating it of (radAngle) radians around an arbitrary pivot lying in (pivotX, pivoty, 
	//in bitmap coordinates), placing it in (srcx, srcy)
	void DrawRectRotatedTo(Bitmap* other, int destx, int desty, int srcx, int srcy, int w, int h, int pivotx, int pivoty, float radAngle); 

	void Clear(unsigned char ColorR, unsigned char ColorG, unsigned char ColorB); //clears this bitmap
	
	//with default font
	void RenderText(int x, int y, char* text, unsigned char ColorR, unsigned char ColorG, unsigned char ColorB); //draws text on this bitmap
	void RenderText(int x, int y, int w, int h, char* text, unsigned char ColorR, unsigned char ColorG, unsigned char ColorB); //draws text on this bitmap, in a box
	//and with custom font
	void RenderText(int x, int y, char* text, Font* font, unsigned char ColorR, unsigned char ColorG, unsigned char ColorB); //draws text on this bitmap
	void RenderText(int x, int y, int w, int h, char* text, Font* font, unsigned char ColorR, unsigned char ColorG, unsigned char ColorB); //draws text on this bitmap, in a box
}; 

#endif