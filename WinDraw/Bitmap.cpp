#include "Bitmap.h"
#include "TGAFile.h"

#include "Font.h"
#include <math.h>

void Bitmap::Create(int w, int h, TGAFile* tgaData)
{

	width = w; 
	height = h; 
	hdc = CreateCompatibleDC(NULL); 
	BITMAPINFO bmi; 
	ZeroMemory(&bmi, sizeof(BITMAPINFO)); 
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w; 
    bmi.bmiHeader.biHeight = h; 
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;         
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = w * h * 4;
	
	HBITMAP hbitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pixelData, NULL, 0x0);
    SelectObject(hdc, hbitmap);

	unsigned __int32* ptr = (unsigned __int32*)pixelData; 
	if(tgaData != NULL) 
	{
		for(int y=0; y<h; y++) 
		{
			TGAFile::TgaColorData* colorData; 
			if((tgaData->Header.imagedescriptor & (1<<5)) != 0)		//top-left or bottom-left origin? 
				colorData= &tgaData->RawData[((h-1)-y) * w];			//top-left, reverse rows
			else
				colorData= &tgaData->RawData[y * w];					//bottom-left, keep rows

			for(int x = 0; x<w; x++, ptr++, colorData++)				//premultiply alpha
			{
				float fPremultAlpha = float(colorData->BgraInfoData.a) / 255.f; 
				unsigned char r = (unsigned char)(float(colorData->BgraInfoData.r) * fPremultAlpha); 
				unsigned char g = (unsigned char)(float(colorData->BgraInfoData.g) * fPremultAlpha); 
				unsigned char b = (unsigned char)(float(colorData->BgraInfoData.b) * fPremultAlpha); 
				*ptr = (colorData->BgraInfoData.a << 24) | (r << 16) | (g <<8) | (b); 
			}
		}
	}
	else
		memset(pixelData, 0, w * h * 4);
	Setup(); 
}

Bitmap::Bitmap(int w, int h): requiresDeletion(true)
{
	Create(w, h, NULL); 
}

Bitmap::Bitmap(TGAFile* file): requiresDeletion(true)
{
	Create(file->Header.width, file->Header.height, file); 
}

Bitmap::~Bitmap()
{
	if(!requiresDeletion) return; 
	DeleteDC(hdc); 
}

Bitmap::Bitmap(HDC drawingDC, int w, int h): requiresDeletion(false)
{
	hdc = drawingDC; 
	width = w; 
	height = h; 
	Setup(); 
}

Bitmap::Bitmap(const char* fileName): requiresDeletion(true)
{
	TGAFile f; 
	if(!f.load(fileName)) return; 
	Create(f.Header.width, f.Header.height, &f); 
}

void Bitmap::Setup()
{
	SetBkMode(hdc, TRANSPARENT); 
	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT); 
	SelectObject(hdc, hFont); 
	SetGraphicsMode(hdc, GM_ADVANCED);
}

void Bitmap::CopyTo(Bitmap* other, int x, int y)
{
	BitBlt(other->hdc, x, y, width, height, hdc, 0, 0, SRCCOPY); 
}

void Bitmap::DrawTo(Bitmap* other, int x, int y)
{
	DrawRectTo(other, x, y, 0, 0, width, height); 
}

void Bitmap::DrawRectTo(Bitmap* other, int destx, int desty, int srcx, int srcy, int w, int h)
{
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.AlphaFormat = AC_SRC_ALPHA;   
    bf.SourceConstantAlpha = 255;

	AlphaBlend(other->hdc, destx, desty, w, h, hdc, srcx, srcy, w, h, bf); 
}

void Bitmap::Clear(unsigned char ColorR, unsigned char ColorG, unsigned char ColorB)
{
	HBRUSH br = CreateSolidBrush(RGB(ColorR, ColorG, ColorB)); 
	RECT rc = {0, 0, width, height}; 
	FillRect(hdc, &rc, br); 
	DeleteObject(br); 
}

void Bitmap::DrawRotatedTo(Bitmap* other, int destx, int desty, int pivotx, int pivoty, float radAngle)
{
	return DrawRectRotatedTo(other, destx, desty, 0, 0, GetWidth(), GetHeight(), pivotx, pivoty, radAngle); 
}

void Bitmap::DrawRectRotatedTo(Bitmap* other, int destx, int desty, int srcx, int srcy, int w, int h, int pivotx, int pivoty, float radAngle)
{
	XFORM xForm; 
	xForm.eM11 = (FLOAT) cosf(radAngle); 
    xForm.eM12 = (FLOAT) sinf(radAngle); 
    xForm.eM21 = (FLOAT) -sinf(radAngle); 
    xForm.eM22 = (FLOAT) cosf(radAngle); 
    xForm.eDx  = (FLOAT) 0.0; 
    xForm.eDy  = (FLOAT) 0.0; 
	POINT pt; 
	SetViewportOrgEx(other->hdc, destx, desty, &pt);		//offset the viewport origin to the pivot and destination to rotate in object space
	SetWorldTransform(other->hdc, &xForm);									//rotate the origin
	
	DrawRectTo(other, -pivotx, -pivoty, srcx, srcy, w, h); 

	xForm.eM11 = (FLOAT) 1.f; 
    xForm.eM12 = (FLOAT) 0.f; 
    xForm.eM21 = (FLOAT) 0.f; 
    xForm.eM22 = (FLOAT) 1.f; 
	SetWorldTransform(other->hdc, &xForm);		//restore world matrix
	SetViewportOrgEx(other->hdc, 0, 0, &pt);	//restore viewport origin
}

void Bitmap::RenderText(int x, int y, char* text, unsigned char ColorR, unsigned char ColorG, unsigned char ColorB)
{
	COLORREF clr = RGB(ColorR, ColorG, ColorB); 
	SetTextColor(hdc, clr); 
	TextOutA(hdc, x, y, text, strlen(text)); 
}

void Bitmap::RenderText(int x, int y, int w, int h, char* text, unsigned char ColorR, unsigned char ColorG, unsigned char ColorB)
{
	COLORREF clr = RGB(ColorR, ColorG, ColorB); 
	SetTextColor(hdc, clr); 
	RECT rc= { x, y, x+w, y+h };
	DrawTextA(hdc, text, strlen(text), &rc, DT_TOP | DT_LEFT | DT_WORDBREAK ); 
}

void Bitmap::RenderText(int x, int y, char* text, Font* font, unsigned char ColorR, unsigned char ColorG, unsigned char ColorB)
{
	if(font && (font->hFont))
	{
		HFONT hOldSelectedFont = (HFONT) SelectObject(hdc, font->hFont);
		RenderText(x, y, text, ColorR, ColorG, ColorB);
		SelectObject(hdc, hOldSelectedFont);
	}
	else
		RenderText(x, y, text, ColorR, ColorG, ColorB);
}

void Bitmap::RenderText(int x, int y, int w, int h, char* text, Font* font, unsigned char ColorR, unsigned char ColorG, unsigned char ColorB)
{
	if(font && (font->hFont))
	{
		HFONT hOldSelectedFont = (HFONT) SelectObject(hdc, font->hFont);
		RenderText(x, y, w, h, text, ColorR, ColorG, ColorB);
		SelectObject(hdc, hOldSelectedFont);
	}
	else
		RenderText(x, y, w, h, text, ColorR, ColorG, ColorB);
}