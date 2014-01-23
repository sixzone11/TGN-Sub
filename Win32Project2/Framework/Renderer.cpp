#include "Renderer.h"

#include "Window.h"

#include <gl/glew.h>

Renderer::Renderer(void) {}
Renderer::~Renderer(void) {}

void Renderer::BeginScene()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Present()
{
	_window->SwapBuffer();
}