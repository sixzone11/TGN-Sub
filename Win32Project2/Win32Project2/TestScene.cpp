#include "StdAfx.h"
#include "TestScene.h"

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
	GLfloat ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
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
	glEnable(GL_DEPTH_TEST);


	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	_cameraZ = 0;
	_cameraAngle = 0;
}

void TestScene::Update(void* context, float dt)
{
}

void TestScene::Render(void* context, float dt)
{
	static float angle = 1;

	glMatrixMode( GL_PROJECTION );

	glLoadIdentity();
	gluPerspective(28.0, 800.0/600.0, 5.0, 19.0);

	glMatrixMode(GL_MODELVIEW);
	//setCamera();
	glLoadIdentity();

	float radian = (float)(_cameraAngle / (180 * M_PI));
	gluLookAt(
		_cameraZ * sin(radian), 0, _cameraZ * cos(radian),
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