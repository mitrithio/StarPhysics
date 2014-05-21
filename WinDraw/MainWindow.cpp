#include "MainWindow.h"
#include "platform.h"
#include "EventHandler.h"
#include "Bitmap.h"
#include <WindowsX.h> 

Bitmap* renderTarget;

namespace KeyboardStatus
{
	void Reset();
	void OnInput(int KeyCode, KeyStatus status);
}

LRESULT WINAPI MainWindow::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	MainWindow* wndPtr = (MainWindow*)GetWindowLongPtr(hWnd, 0); 
    switch( msg )
    {
	case PRF_ERASEBKGND:
		return TRUE; 
	case WM_CREATE: 
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*) lParam; 
			renderTarget = new Bitmap(pCreate->cx, pCreate->cy);
		}
		break; 
	case WM_PAINT: 
		{
			PAINTSTRUCT ps; 
			RECT rc; 
			GetClientRect(hWnd, &rc); 
			HDC dc = BeginPaint(hWnd, &ps); 
			if(wndPtr->eventHandler != NULL) 
			{
				Bitmap bmp(dc, rc.right - rc.left, rc.bottom - rc.top); 
				renderTarget->CopyTo(&bmp, 0, 0); 
			}
			EndPaint(hWnd, &ps); 
		}
		return 0; 
	case WM_KEYUP: 
		if(wndPtr->eventHandler != NULL) 
			wndPtr->eventHandler->OnInput(wParam, KeyReleased); 
		KeyboardStatus::OnInput(wParam, KeyReleased); 
		break; 
	case WM_KEYDOWN: 
		if((lParam & (1 << 30)) != 0) break; //already sent anyway
		if(wndPtr->eventHandler != NULL)
			if((lParam & (1<<30)) == 0)
				wndPtr->eventHandler->OnInput(wParam, KeyPressed); 
		KeyboardStatus::OnInput(wParam, KeyPressed); 
		break; 
	case WM_LBUTTONDOWN: 
	case WM_LBUTTONUP: 
	case WM_RBUTTONDOWN: 
	case WM_RBUTTONUP: 
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			if(wndPtr->eventHandler != NULL)
			{
				switch(msg)
				{
					case WM_LBUTTONDOWN: 
						wndPtr->eventHandler->OnMouseInput(xPos, yPos, LMouse, KeyPressed); SetCapture(hWnd); break; 
					case WM_LBUTTONUP: 
						wndPtr->eventHandler->OnMouseInput(xPos, yPos, LMouse, KeyReleased); ReleaseCapture(); break; 
					case WM_RBUTTONDOWN: 
						wndPtr->eventHandler->OnMouseInput(xPos, yPos, RMouse, KeyPressed); SetCapture(hWnd);break; 
					case WM_RBUTTONUP: 
						wndPtr->eventHandler->OnMouseInput(xPos, yPos, RMouse, KeyReleased); ReleaseCapture(); break; 
				}
			}
		}
		break; 
	case WM_MOUSEMOVE: 
		if(wndPtr->eventHandler != NULL)
		{
			MouseKey key = ((wParam & MK_LBUTTON) != 0) ? LMouse : ((wParam & MK_RBUTTON) != 0)? RMouse : No_Key; 
			wndPtr->eventHandler->OnMouseInput(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), key, MouseMove);
		}
		break; 
	case WM_DESTROY:
		delete renderTarget; 
		renderTarget = NULL; 
		wndPtr->handle = NULL; 
        return 0;
    }
    return DefWindowProc( hWnd, msg, wParam, lParam );
}

void MainWindow::Create(int w, int h, char* title)
{
	if(handle != NULL) return; 
	handle = ::createAppWindow(w, h, title, this); 
}

void MainWindow::DispatchInput()
{
	MSG msg;
    ZeroMemory( &msg, sizeof( msg ) );
	if(handle == NULL) return; 
	KeyboardStatus::Reset(); 
    while( PeekMessage( &msg, handle, 0U, 0U, PM_REMOVE )  != 0)
    {
		TranslateMessage( &msg );
		DispatchMessage( &msg );
    }
}

void MainWindow::Redraw()
{
	if((eventHandler!= NULL) && (renderTarget != NULL))
	{
		renderTarget->Clear(0,0,0); 
		eventHandler->OnRender(renderTarget); 
	}
	else
		return; 
	InvalidateRect(handle, NULL, FALSE); 
	MSG msg;
    ZeroMemory( &msg, sizeof( msg ) );
	if(handle == NULL) return; 
	while( PeekMessage( &msg, handle, WM_PAINT, WM_PAINT, PM_REMOVE )  != 0)
    {
		TranslateMessage( &msg );
		DispatchMessage( &msg );
    }
}