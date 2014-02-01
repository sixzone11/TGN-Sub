#include "Window.h"

#include <gl/glew.h>
#include <GL/wglew.h>

Window::Window( HINSTANCE hInst, WNDPROC proc, const TCHAR* appTitle, const TCHAR* defaultClassName )
	: _width(800), _height(600)
{
	// Store key integer value corresponding to IDs
	_windowTitle		= appTitle;
	_windowClassName	= defaultClassName;

	// If you want to use GetModuleHandle(NULL), of coursely, you can do that.
	// But by passing the parameter hInst,
	// It will be more explict that let you code that initiate Window in root routine.
	_hInst				= hInst;
}


Window::~Window(void)
{
}

//
//  FUNCTION: RegisterClass()
//
//  PURPOSE: Registers the window class.
//

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
void Window::InitInstance( int nCmdShow, int width, int height )
{
	_width = width;
	_height = height;

	CreateWindow( _windowClassName, _windowTitle, WS_OVERLAPPEDWINDOW,
		0, 0, _width, _height,
		NULL, NULL, _hInst, NULL );

	if ( !_hWnd )
	{
		throw false;
	}

	ShowWindow( _hWnd, nCmdShow );
	UpdateWindow( _hWnd );
}

LRESULT Window::Procedure(  HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	int wmId, wmEvent;

	switch( msg )
	{
	case WM_CREATE:
		_hWnd = hWnd;
		EnableOpenGL( 4, 2 );
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
		return DefWindowProc( hWnd, msg, wParam, lParam );
	}
	return 0;
}

void Window::LoadingGLFunctions()
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
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

	int  letWindowsChooseThisPixelFormat;
	letWindowsChooseThisPixelFormat = ChoosePixelFormat( _hDC, &pfd ); 
	SetPixelFormat( _hDC, letWindowsChooseThisPixelFormat, &pfd );

	HGLRC ourOpenGLFalseContext = wglCreateContext( _hDC );
	wglMakeCurrent ( _hDC, ourOpenGLFalseContext );

	LOG("OPENGL VERSION: %s", (char*)glGetString(GL_VERSION) );

	if( glewInit() != GLEW_OK )
	{
		throw false;
	}

	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( ourOpenGLFalseContext );
}

void Window::EnableOpenGL( int majorVersion, int minorVersion )
{
	// get the device context (DC)
	_hDC = GetDC( _hWnd );

	LoadingGLFunctions();

	if( majorVersion <= 2 )
	{
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

		format = ChoosePixelFormat( _hDC, &pfd );
		SetPixelFormat( _hDC, format, &pfd );

		// create and enable the render context (RC)
		_hGLRC = wglCreateContext( _hDC );
	}
	else if( WGLEW_ARB_create_context && WGLEW_ARB_pixel_format )
	{
		const int pfList[] = {
			WGL_DRAW_TO_WINDOW_ARB,	GL_TRUE, 
			WGL_SUPPORT_OPENGL_ARB,	GL_TRUE, 
			WGL_DOUBLE_BUFFER_ARB,	GL_TRUE, 
			WGL_PIXEL_TYPE_ARB,		WGL_TYPE_RGBA_ARB, 
			WGL_COLOR_BITS_ARB,		32, 
			WGL_DEPTH_BITS_ARB,		24, 
			WGL_STENCIL_BITS_ARB,	8, 
			0 // End of attributes list
		};
		int contextList[] = 
		{ 
			WGL_CONTEXT_MAJOR_VERSION_ARB,	majorVersion, 
			WGL_CONTEXT_MINOR_VERSION_ARB,	minorVersion, 
			WGL_CONTEXT_FLAGS_ARB,			WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, 
			0 // End of attributes list
		};

		int iPixelFormat, iNumFormats; 
		wglChoosePixelFormatARB(_hDC, pfList, NULL, 1, &iPixelFormat, ( UINT* )&iNumFormats ); 

		// PFD seems to be only redundant parameter now
		PIXELFORMATDESCRIPTOR pfd;
		if(!SetPixelFormat( _hDC, iPixelFormat, &pfd ) )
			throw false;

		_hGLRC = wglCreateContextAttribsARB( _hDC, 0, contextList ); 
	}

	// If everything went OK
	if( _hGLRC ) wglMakeCurrent(_hDC, _hGLRC);
}

void Window::DisableOpenGL()
{
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( _hGLRC );
	ReleaseDC( _hWnd, _hDC );
}

void Window::SwapBuffer()
{
	SwapBuffers( _hDC );
}