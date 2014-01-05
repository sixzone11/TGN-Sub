#pragma once

#include "Macro.h"

#include "Window.h"

class PlatformBase;

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
	void		SetWindow(Window* window);

	GET_ACCESSOR(InstanceHandle, HINSTANCE, _hInst);


public:
	GET_ACCESSOR(Window, Window*, _window);


private:
	Window*				_window;

	HINSTANCE			_hInst;
	LARGE_INTEGER		_animationInterval;


protected:
	HACCEL				_hAccelTable;
};

