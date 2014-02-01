#include "Window.h"

#include "Renderer.h"

Renderer::Renderer(void) {}

Renderer::~Renderer(void)
{
	glDeleteVertexArrays(1, &_vertexArrayID);
}


void Renderer::Initialize()
{
	// vertex array generate & bind
	GLuint _vertexArrayID;
	glGenVertexArrays( 1, &_vertexArrayID );
	glBindVertexArray( _vertexArrayID );
}

void Renderer::BeginScene()
{
	glClear( GL_COLOR_BUFFER_BIT );//| GL_DEPTH_BUFFER_BIT );
}

void Renderer::Present()
{
	_window->SwapBuffer();
}