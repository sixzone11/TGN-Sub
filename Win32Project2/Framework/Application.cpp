#include "Application.h"

#include "PlatformBase.h"

CApplication::CApplication(PlatformBase* platform)
{
	_hInst = GetModuleHandle(NULL);
}


CApplication::~CApplication(void)
{
}


int CApplication::Run()
{
	MSG msg;
	HACCEL hAccelTable;

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;


	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nLast);

	hAccelTable = LoadAccelerators(_hInst, MAKEINTRESOURCE(IDC_WIN32PROJECT2));

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
			}
			else
			{
				Sleep(0);
			}
			continue;

			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
			glClear( GL_COLOR_BUFFER_BIT );
			
			glPushMatrix();
			glBegin( GL_TRIANGLES );
			glColor3f( 1.0f, 0.0f, 0.0f ); glVertex2f( 0.0f, 1.0f );
			glColor3f( 0.0f, 1.0f, 0.0f ); glVertex2f( 0.87f, -0.5f );
			glColor3f( 0.0f, 0.0f, 1.0f ); glVertex2f( -0.87f, -0.5f );
			glEnd();
			glPopMatrix();
			
			SwapBuffers( hdc );

			continue;
		}

		if(msg.message == WM_QUIT)
		{
			break;
		}
		
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}