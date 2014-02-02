#include "StdAfx.h"
#include "TestScene.h"

#include "PlatformBase.h"

#include <GL/glew.h>

#define _USE_MATH_DEFINES
#include <math.h>

TestScene::TestScene(void)
{
	Initialize(NULL);
}


TestScene::~TestScene(void)
{
	Release(NULL);
}


void TestScene::Initialize(void* context)
{
	/*GLfloat ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat diffuse[] = {.8f, .8f, .4f, 1.0f};
	GLfloat specular[] = {.8f, 0.3f, 0.5f, 1.0f};
	GLfloat position[] = {0.0f, 0.0f, 5.0f, 0.0f};
	GLfloat lmodel_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat local_view[] = {0.0f};

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
	glEnable(GL_DEPTH_TEST);*/

	glClearColor( 0.f, .5f, 0.f, 1.f );

	_cameraZ = 0;
	_cameraAngle = 0;

	// Set values
	_triangle[0].Set( 0, 1, 0 );//, 0, 1, -1 );
	_triangle[1].Set( -.5f, 0, 0 );//, -1.f, -1.f, 0 );
	_triangle[2].Set( .5f, 0, 0 ); //, 1, -1, 0 );
	
	_color[0].Set( 1, 0, 0 );
	_color[1].Set( 0, 1, 0 );
	_color[2].Set( 0, 0, 1 );

	LOG("triangle size: %d", sizeof(_triangle) );
	
	//// vertex buffer generate
	glGenBuffers( 2, _vertexBufferObject );

	//// triangle bind
	glBindBuffer( GL_ARRAY_BUFFER, _vertexBufferObject[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof( _triangle ), _triangle, GL_STATIC_DRAW );
	
	// enable attrib index;
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );

	// for color like above
	glBindBuffer( GL_ARRAY_BUFFER, _vertexBufferObject[1] );
	glBufferData( GL_ARRAY_BUFFER, sizeof( _color ), _color, GL_STATIC_DRAW );
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, NULL );

	vsh.LoadShader( "shader.vsh", GL_VERTEX_SHADER );
	fsh.LoadShader( "shader.fsh", GL_FRAGMENT_SHADER );

	prog.CreateProgram();
	prog.AddShaderToProgram( &vsh );
	prog.AddShaderToProgram( &fsh );

	prog.LinkProgram();
	prog.UseProgram();
}

void TestScene::Update(void* context, float dt)
{
	//_triangle[0].Set( 0, 1, 0, 0, 1, -1 );
	//_triangle[1].Set( -.5f, 0, 0, -1.f, -1.f, 0 );
	//_triangle[2].Set( .5f, 0, 0, 1, -1, 0 );
}

void TestScene::Render(void* context, float dt)
{
	static float angle = 1;

	glDrawArrays( GL_TRIANGLES, 0, 3 );

	glFlush();
}

void TestScene::Release(void* context)
{
}

void TestScene::HardwereResponse(void* context, const CInput* input)
{
	if( input->IsKeyPressed( DIK_UPARROW ) )
	{
		_cameraZ -= 0.00001f;
	}

	if( input->IsKeyPressed( DIK_DOWNARROW ) )
	{
		_cameraZ += 0.00001f;
	}

	if( input->IsKeyPressed( DIK_LEFTARROW ) )
	{
		_cameraAngle -= .001f;
	}

	if( input->IsKeyPressed( DIK_RIGHTARROW ) )
	{
		_cameraAngle += .001f;
	}
}

void TestScene::ShaderInitialize()
{
	// Compile shader
	unsigned vertexShader;
	const GLchar* source = "test.vsh";
	vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShader, 1, &source, 0 );
	glCompileShader( vertexShader );
	
	int compileStatus;
	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &compileStatus );

	if( compileStatus == GL_FALSE )
	{
		char msg[256];
		glGetShaderInfoLog( vertexShader, sizeof(msg), 0, msg );
		return;
	}

	_programHandle = glCreateProgram();

	glAttachShader( _programHandle, vertexShader );
	// ps

	glBindAttribLocation( _programHandle, 0, "vpos" );
	glBindAttribLocation( _programHandle, 1, "vnorm" );

	int linkStatus;
	glLinkProgram( _programHandle );
	glGetProgramiv( _programHandle, GL_LINK_STATUS, &linkStatus );
	if( linkStatus == GL_FALSE )
	{
		char msg[256];
		glGetProgramInfoLog( _programHandle, sizeof(msg), 0, msg );
		_programHandle = 0;
		return;
	}

	glUseProgram( _programHandle );
}