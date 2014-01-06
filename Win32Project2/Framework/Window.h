#pragma once

#include <Windows.h>

#include "Macro.h"

class Window
{
public:
	Window( HINSTANCE hInst, WNDPROC proc, const TCHAR* appTitle, const TCHAR* defaultClassName );
	~Window();


public:
	void			InitInstance( int nCmdShow, int width, int height );


public:
	LRESULT			Procedure( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );


private:
	void			EnableOpenGL();
	void			DisableOpenGL();


public:
	void			SwapBuffer();


public:
	GET_ACCESSOR(Instance, HINSTANCE, _hInst)
	GET_ACCESSOR(HWND, HWND, _hWnd)
	GET_ACCESSOR(Width, int, _width)
	GET_ACCESSOR(Height, int, _height)


private:
	HINSTANCE		_hInst;
	HWND			_hWnd;
	HDC				_hDC;
	HGLRC			_hGLRC;

	const TCHAR*	_windowTitle;
	const TCHAR*	_windowClassName;

	int				_width;
	int				_height;
};