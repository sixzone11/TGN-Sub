#include "Application.h"

CApplication::CApplication()
	: _hAccelTable(NULL)
{
	_hInst = GetModuleHandle(NULL);
}


CApplication::~CApplication(void)
{
	if(_window) delete _window;
}


void CApplication::SetWindow(Window* window)
{
	_window = window;
	_window->InitInstance( true );
}


int CApplication::Run()
{
	MSG msg;

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;


	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nLast);


	if(ApplicationDidFinishInitialize() == false)
	{
		return -1;
	}

	// Main message loop:
	while(TRUE)
	{
		if(! PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			QueryPerformanceCounter(&nNow);

			// If it's the time to draw next frame, draw it, else sleep a while.
			if (nNow.QuadPart - nLast.QuadPart > _animationInterval.QuadPart)
			{
				nLast.QuadPart = nNow.QuadPart;

				// MainLoop
				_window->Update(0);
			}
			else
			{
				Sleep(0);
			}
			continue;
		}

		if(msg.message == WM_QUIT)
		{
			break;
		}
		
		if (!TranslateAccelerator(msg.hwnd, _hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}