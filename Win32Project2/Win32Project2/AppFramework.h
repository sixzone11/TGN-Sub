#pragma once

#include "Application.h"

class CAppFramework : private CApplication
{
public:
	CAppFramework(Window* window);
	~CAppFramework(void);


private:
	virtual bool		ApplicationDidFinishInitialize();
};