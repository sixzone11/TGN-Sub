#include "Window.h"

#include "Renderer.h"

Renderer::Renderer(void) {}

Renderer::~Renderer(void)
{
	glDeleteVertexArrays(1, &_vertexArrayID);
}


void Renderer::Initialize()
{
}

void Renderer::BeginScene()
{
	glClear( GL_COLOR_BUFFER_BIT );//| GL_DEPTH_BUFFER_BIT );
}

void Renderer::Present()
{
	_window->SwapBuffer();
}