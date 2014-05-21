#ifndef PLATFORM_H
#define PLATFORM_H
#include "WinDrawSystemApi.h"
#include "MainWindow.h"

//Win-32 specific header. Hic sunt leones (cit.)

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ); 

inline void setupWorkDirectory()
{
	char appdir[512]; 
	GetModuleFileNameA(GetModuleHandle(NULL), appdir, 512);
	strrchr(appdir, '\\')[1] = 0; 
	SetCurrentDirectoryA(appdir); 
}

inline HWND createAppWindow(int screenWidth, int screenHeight, const char* gameName, void* extraData)
{
	short tmp[512]; 
	for(unsigned int i=0; i<strlen(gameName) +1; i++) 
		tmp[i] = gameName[i]; 
	WNDCLASSEXA wc =
    {
        sizeof( WNDCLASSEXA ), CS_CLASSDC, MainWindow::MsgProc, 0L, sizeof(void*),
        GetModuleHandle( NULL ), NULL, LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(BLACK_BRUSH), NULL,
        "WndClass4WinDraw", NULL
    };
    RegisterClassExA( &wc );
	RECT wndRect; 
	wndRect.left = wndRect.top = 0; 
	wndRect.bottom = screenHeight; 
	wndRect.right = screenWidth; 
	AdjustWindowRectEx(&wndRect, WS_OVERLAPPEDWINDOW, FALSE, 0); 
    HWND hWnd = CreateWindowExA(0, "WndClass4WinDraw", (char*)tmp,
                              WS_OVERLAPPEDWINDOW, 50, 50, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top,
                              NULL, NULL, wc.hInstance, NULL );
	SetWindowLongPtr(hWnd, 0, (LONG)extraData); 
    ShowWindow( hWnd, SW_SHOWDEFAULT );
    UpdateWindow( hWnd );
	return hWnd; 
}

inline void initHiResTimer(double* freq)
{
	LARGE_INTEGER li; 
    QueryPerformanceFrequency(&li);
    *freq = double(li.QuadPart);
}

inline float getHiResTime(double freq)
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return (float(li.QuadPart/freq));
}

inline void wait(float seconds)
{
	if(seconds <0) return; 
	DWORD ms = (DWORD) (seconds* 1000.f); 
	Sleep(ms); 
}

#endif // PLATFORM_H
