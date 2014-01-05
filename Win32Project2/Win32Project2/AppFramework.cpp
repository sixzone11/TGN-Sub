#include "StdAfx.h"
#include "AppFramework.h"

FRAMEWORK_SETTING

CAppFramework::CAppFramework(Window* window)
{
	FRAMEWORK_BINDING

	InitialMainWindow(window);

	_hAccelTable = LoadAccelerators(GetInstanceHandle(), MAKEINTRESOURCE(IDC_WIN32PROJECT2));
}


CAppFramework::~CAppFramework(void)
{
}


bool CAppFramework::ApplicationDidFinishInitialize()
{
	return true;
}

void CAppFramework::ApplicationWillMinimize()
{
}

void CAppFramework::ApplicationWillTerminate()
{
}