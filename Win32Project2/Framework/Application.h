#pragma once

#include "Macro.h"

#include "Window.h"

class PlatformBase;

#define FRAMEWORK_SETTING \
	static CApplication* app = NULL; CApplication* CApplication::GetInstance() { if(app) { return app; } return NULL; }
#define FRAMEWORK_BINDING \
	if(app == NULL) { app = this; } else { throw false; }


class CApplication
{
protected:
	CApplication();
	~CApplication(void);


public:
	static CApplication*	GetInstance();


protected:
	virtual bool		ApplicationDidFinishInitialize() { return false; }
	virtual void		ApplicationWillMinimize() {}
	virtual void		ApplicationWillTerminate() {}


public:
	int Run();


protected:
	void		InitialMainWindow(Window* window);


protected:
	GET_ACCESSOR(InstanceHandle, HINSTANCE, _hInst);


public:
	GET_ACCESSOR(Window, Window*, _window);


public:
	void		SetAnimationInterval(double t);


private:
	Window*				_window;

	HINSTANCE			_hInst;
	LARGE_INTEGER		_animationInterval;


protected:
	HACCEL				_hAccelTable;
};

