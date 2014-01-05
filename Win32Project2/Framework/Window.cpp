#include "Window.h"
#include "Renderer.h"

#include <gl/GL.h>
#include <gl/GLU.h>

float camera_z = 0;

Window::Window( HINSTANCE hInst, WNDPROC proc, const TCHAR* appTitle, const TCHAR* defaultClassName )
{
	// Store key integer value corresponding to IDs
	_windowTitle		= appTitle;
	_windowClassName	= defaultClassName;

	// Store instance handle in our global variable
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
void Window::InitInstance( int nCmdShow )
{
	CreateWindow( _windowClassName, _windowTitle, WS_OVERLAPPEDWINDOW,
		0, 0, 800, 600,
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

	case WM_KEYDOWN:
		camera_z += .5;
		break;

	case WM_KEYUP:
		break;

	default:
		return DefWindowProc( hWnd, msg, wParam, lParam );
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

	GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat diffuse[] = {.8, .8, .4, 1.0};
	GLfloat specular[] = {.8, 0.3, 0.5, 1.0};
	GLfloat position[] = {0.0, 0.0, 5.0, 0.0};
	GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat local_view[] = {0.0};


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glFrontFace(GL_CCW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
}

void Window::DisableOpenGL()
{
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( _hGLRC );
	ReleaseDC( _hWnd, _hDC );
}

void Window::Update(float dt)
{
	static double angle = 1;
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode( GL_PROJECTION );

	glLoadIdentity();
	gluPerspective(28.0, 800.0/600.0, 5.0, 19.0);

	glMatrixMode(GL_MODELVIEW);
	//setCamera();
	glLoadIdentity();
	gluLookAt(
		0, 0, camera_z,
		0, 0, 0,
		0, 1, 0);

	//drawAxis();

	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0, 0.0, 0);
	glRotatef(angle, 0, 0, 1);
	angle += 1;

	//drawAnObject();
	glPushMatrix();
	glBegin( GL_TRIANGLES );
	glColor3f( 1.0f, 0.0f, 0.0f ); glVertex2f( 0.0f, 1.0f );
	glColor3f( 0.0f, 1.0f, 0.0f ); glVertex2f( 0.87f, -0.5f );
	glColor3f( 0.0f, 0.0f, 1.0f ); glVertex2f( -0.87f, -0.5f );
	glEnd();
	glPopMatrix();

	glFlush();

	

	

	SwapBuffers( _hDC );
}