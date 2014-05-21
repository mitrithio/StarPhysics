#ifndef WINDRAW_FONT_H
#define WINDRAW_FONT_H

#include "Bitmap.h"
#include <wingdi.h>


class Font
{
private:
	//copy constructor and assignment operators are disabled for this class
	Font(Font&) {}
	Font& operator=(Font&) {}

protected:

	//font handler is accessible from these functions
	friend void Bitmap::RenderText(int x, int y, char* text, Font* font, unsigned char ColorR, unsigned char ColorG, unsigned char ColorB); //draws text on this bitmap
	friend void Bitmap::RenderText(int x, int y, int w, int h, char* text, Font* font, unsigned char ColorR, unsigned char ColorG, unsigned char ColorB); //draws text on this bitmap, in a box

	HFONT hFont;

public:
	Font(int Height, int Width, int Weight, bool Italic, bool Underline, bool StrikeOut, const char* FaceName);
	~Font();
	bool IsValid() const;
};

#endif