#include "Application.h"

#include "FrameworkManager.h"

CApplication::CApplication()
	: _hAccelTable(NULL), _input(NULL)
{
	_hInst = GetModuleHandle(NULL);


	// by default
	SetAnimationInterval(1.0 / 60);
}


CApplication::~CApplication(void)
{
	if(_window)
	{
		delete _window;
	}
	
	if(_input)
	{
		_input->Shutdown();
		delete _input;
	}
}


void CApplication::InitialMainWindow(Window* window)
{
	int width = 800, height = 600;

	SetMainWindowSize(width, height);

	_window = window;
	_window->InitInstance( true, width, height );

	Renderer::GetInstance()->SetWindow(_window);

	_input = new CInput;
	_input->Initialize(_window);

	Renderer::GetInstance()->Initialize();
}

void CApplication::SetAnimationInterval(double interval)
{
	LARGE_INTEGER nFreq;
	QueryPerformanceFrequency(&nFreq);
	_animationInterval.QuadPart = (LONGLONG)(interval * nFreq.QuadPart);
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
			_input->Frame();

			QueryPerformanceCounter(&nNow);

			// If it's the time to draw next frame, draw it, else sleep a while.
			if (nNow.QuadPart - nLast.QuadPart > _animationInterval.QuadPart)
			{
				nLast.QuadPart = nNow.QuadPart;

				// MainLoop
				FrameworkManager::GetInstance()->Update(0);
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