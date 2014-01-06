#include "StdAfx.h"
#include "AppFramework.h"

#include "FrameworkManager.h"

#include "TestScene.h"

FRAMEWORK_SETTING /*("Win32Project2")*/

CAppFramework::CAppFramework(Window* window)
{
	FRAMEWORK_BINDING

	InitialMainWindow(window);

	_hAccelTable = LoadAccelerators(GetWindow()->GetInstance(),
		MAKEINTRESOURCE(IDC_WIN32PROJECT2));
}


CAppFramework::~CAppFramework(void)
{
}


bool CAppFramework::ApplicationDidFinishInitialize()
{
	CSceneManager::GetInstance()->AddScene(new TestScene, "Test");

	return true;
}

void CAppFramework::ApplicationWillMinimize()
{
}

void CAppFramework::ApplicationWillTerminate()
{
}