#pragma once

#include <Windows.h>

class Window
{
public:
	Window( HINSTANCE hInst, WNDPROC proc, int nCmdShow, int appTitle, int defaultClassName );
	~Window();


private:
	ATOM			RegisterClass( WNDPROC proc, TCHAR* title, TCHAR* className );
	void			InitInstance( int nCmdShow, TCHAR* title, TCHAR* className );
	LRESULT			Procedure( UINT msg, WPARAM wParam, LPARAM lParam );


private:
	void			EnableOpenGL();
	void			DisableOpenGL();


private:
	HINSTANCE		_hInst;
	HWND			_hWnd;
	HDC				_hDC;
	HGLRC			_hGLRC;

	UINT			_windowTitleID;
	UINT			_windowClassNameID;
};