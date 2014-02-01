#pragma once

#include "Macro.h"

#include <gl/glew.h>

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
	SET_ACCESSOR( Window, Window*, _window )
	

public:
	void Initialize();


public:
	void BeginScene();
	void Present();


private:
	Window*		_window;
	GLuint		_vertexArrayID;
};

