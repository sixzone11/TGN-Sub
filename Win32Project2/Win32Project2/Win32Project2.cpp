// Win32Project2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project2.h"

#include "AppFramework.h"

#include <gl/GL.h>

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")

// Forward declarations of functions included in this code module:
ATOM				RegisterWindow( HINSTANCE hInst, TCHAR* className );
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	try
	{
		TCHAR* className = _T("Test");
		if(RegisterWindow( hInstance, className ) == 0)
			throw false;

		Window* window = new Window(hInstance, WndProc, _T("Test"), className );
		CAppFramework framework(window);

		int result;

		result = CApplication::GetInstance()->Run();

		return result;
	}
	catch( bool )
	{
		DWORD errorNo = GetLastError();

		return 0;
	}
}

ATOM RegisterWindow( HINSTANCE hInst, TCHAR* className )
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof( WNDCLASSEX );

	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInst;
	wcex.hIcon			= LoadIcon( hInst, MAKEINTRESOURCE( IDI_WIN32PROJECT2 ) );
	wcex.hCursor		= LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground	= (HBRUSH)( COLOR_WINDOW+1 );
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE( IDC_WIN32PROJECT2 );
	wcex.lpszClassName	= className;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE( IDI_SMALL ) );

	return RegisterClassEx(&wcex);
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return CApplication::GetInstance()->GetWindow()->Procedure(hWnd, message, wParam, lParam);
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
