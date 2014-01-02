#pragma once

#include <Windows.h>

class PlatformBase;

class CApplication
{
public:
	CApplication(PlatformBase* platform);
	~CApplication(void);


public:
	int Run();


private:
	PlatformBase*		_platform;

	HINSTANCE			_hInst;
	LARGE_INTEGER		_animationInterval;
};

