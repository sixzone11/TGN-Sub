#pragma once

#include <Windows.h>

class Window
{
public:
	Window( HINSTANCE hInst, WNDPROC proc, const TCHAR* appTitle, const TCHAR* defaultClassName );
	~Window();


public:
	void			InitInstance( int nCmdShow );


public:
	LRESULT			Procedure( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );


private:
	void			EnableOpenGL();
	void			DisableOpenGL();


public:
	void			Update(float dt);


private:
	HINSTANCE		_hInst;
	HWND			_hWnd;
	HDC				_hDC;
	HGLRC			_hGLRC;

	const TCHAR*	_windowTitle;
	const TCHAR*	_windowClassName;
};