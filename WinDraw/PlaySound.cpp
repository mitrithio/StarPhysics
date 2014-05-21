#include "PlaySound.h"
#include <Windows.h>

bool PlaySoundFromFile(const char* filename)
{
	/*
	WCHAR wideCharFilename[255];
	int i = 0;
	for(; i < 255 && filename[i] != '\0'; ++i);
	MultiByteToWideChar(0, 0, filename, i, wideCharFilename, 255);
	*/
	return PlaySoundA(filename,  NULL, SND_FILENAME | SND_ASYNC );
}
