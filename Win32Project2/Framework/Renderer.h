#pragma once

#include "Macro.h"

class Window;

class PlatformBase;

class Renderer
{
private:
	Renderer(void);
	~Renderer(void);


public:
	SINGLETON_DEFINE( Renderer );


public:
	void SetWindow(Window* window);
	

public:
	void BeginScene();
	void Present();


private:
	Window* _window;
};

