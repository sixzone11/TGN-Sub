#pragma once

#include "Macro.h"

#include "Window.h"
#include "Input.h"

class PlatformBase;

#define FRAMEWORK_SETTING \
	static CApplication* app = NULL; CApplication* CApplication::GetInstance() { if(app) { return app; } return NULL; }
// (app_name) \
//	static const char* appName = app_name;
#define FRAMEWORK_BINDING \
	if(app == NULL) { app = this; } else { throw false; }
#define FRAMEWORK_APP_NAME app_name


class CApplication
{
protected:
	CApplication();
	~CApplication(void);


public:
	static CApplication*	GetInstance();


protected:
	virtual void		SetMainWindowSize(int& width, int& height) {}
	virtual bool		ApplicationDidFinishInitialize() { return false; }
	virtual void		ApplicationWillMinimize() {}
	virtual void		ApplicationWillTerminate() {}


public:
	int Run();


protected:
	void		InitialMainWindow(Window* window);


public:
	GET_ACCESSOR(Window, Window*, _window);


public:
	void		SetAnimationInterval(double t);


private:
	Window*				_window;
	CInput*				_input;

	HINSTANCE			_hInst;
	LARGE_INTEGER		_animationInterval;


protected:
	HACCEL				_hAccelTable;
};

