#include "Window.h"
#include "Renderer.h"


Window::Window( HINSTANCE hInst, WNDPROC proc, int nCmdShow, int appTitle, int defaultClassName )
{
	// Store key integer value corresponding to IDs
	_windowTitleID		= appTitle;
	_windowClassNameID	= defaultClassName;

	// Store instance handle in our global variable
	_hInst				= hInst;

	// Load default window title and window class name
	const int	size = 128;
	TCHAR		title[size];
	TCHAR		className[size];

	LoadString(_hInst, _windowTitleID, title, size);
	LoadString(_hInst, _windowClassNameID, className, size);

	// Register window class and initialize window instance
	RegisterClass(proc, title, className);
	InitInstance(nCmdShow, title, className);
}


Window::~Window(void)
{
}

//
//  FUNCTION: RegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM Window::RegisterClass( WNDPROC proc, TCHAR* title, TCHAR* className )
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof( WNDCLASSEX );

	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc	= proc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= _hInst;
	wcex.hIcon			= NULL; //LoadIcon( _hInst, MAKEINTRESOURCE( IDI_WIN32PROJECT2 ) );
	wcex.hCursor		= LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground	= (HBRUSH)( COLOR_WINDOW+1 );
	wcex.lpszMenuName	= NULL; //MAKEINTRESOURCE( _windowClassNameID );
	wcex.lpszClassName	= className;
	wcex.hIconSm		= NULL; //LoadIcon(wcex.hInstance, MAKEINTRESOURCE( IDI_SMALL ) );

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
void Window::InitInstance( int nCmdShow, TCHAR* title, TCHAR* className )
{
	_hWnd = CreateWindow( className, title, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, NULL, _hInst, NULL );

	if ( !_hWnd )
	{
		throw FALSE;
	}

	ShowWindow( _hWnd, nCmdShow );
	UpdateWindow( _hWnd );
}

LRESULT Window::Procedure( UINT msg, WPARAM wParam, LPARAM lParam )
{
	int wmId, wmEvent;

	switch( msg )
	{
	case WM_CREATE:
		EnableOpenGL();
		break;

	//case WM_COMMAND:
	//	wmId    = LOWORD( wParam );
	//	wmEvent = HIWORD( wParam );

	//	// Parse the menu selections:
	//	switch( wmId )
	//	{
	//	case IDM_EXIT:
	//		DestroyWindow( _hWnd );
	//		break;
	//	default:
	//		return DefWindowProc( _hWnd, msg, wParam, lParam );
	//	}
	//	break;

	case WM_DESTROY:
		DisableOpenGL();
		PostQuitMessage( 0 );
		break;

	default:
		return DefWindowProc( _hWnd, msg, wParam, lParam );
	}
	return 0;
}

void Window::EnableOpenGL()
{
	//PIXELFORMATDESCRIPTOR pfd;
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof( PIXELFORMATDESCRIPTOR ),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		32,                        //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                        //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	int format;
	
	// get the device context (DC)
	_hDC = GetDC( _hWnd );
	
	format = ChoosePixelFormat( _hDC, &pfd );
	SetPixelFormat( _hDC, format, &pfd );
	
	// create and enable the render context (RC)
	_hGLRC = wglCreateContext( _hDC );
	wglMakeCurrent( _hDC, _hGLRC );
}

void Window::DisableOpenGL()
{
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( _hGLRC );
	ReleaseDC( _hWnd, _hDC );
}
