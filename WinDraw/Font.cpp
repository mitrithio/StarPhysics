#include "Font.h"

Font::Font(int cHeight, int cWidth, int cWeight, bool bItalic, bool bUnderline, bool bStrikeOut, const char* pszFaceName)
	: hFont(CreateFontA(cHeight, cWidth, 0, 0, cWeight, bItalic, bUnderline, bStrikeOut, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, pszFaceName))
{
}

Font::~Font()
{
	if(hFont)
		DeleteObject(hFont);
}

bool Font::IsValid() const
{
	return hFont != NULL;
}