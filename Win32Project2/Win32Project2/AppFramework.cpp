#include "StdAfx.h"
#include "AppFramework.h"

static CApplication*		g_instance = NULL;

CApplication* CApplication::GetInstance()
{
	if(g_instance)
	{
		return g_instance;
	}
	return NULL;
}


CAppFramework::CAppFramework(Window* window)
{
	if(g_instance == NULL)
	{
		g_instance = this;

		SetWindow(window);

		_hAccelTable = LoadAccelerators(GetInstanceHandle(), MAKEINTRESOURCE(IDC_WIN32PROJECT2));
	}
	else
	{
		throw false;
	}
}


CAppFramework::~CAppFramework(void)
{
}


bool CAppFramework::ApplicationDidFinishInitialize()
{
	return true;
}