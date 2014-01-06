#include "FrameworkManager.h"


FrameworkManager::FrameworkManager(void)
{
}


FrameworkManager::~FrameworkManager(void)
{
}


void FrameworkManager::Update(float dt)
{
	CSceneManager::GetInstance()->Update(NULL, dt);

	Renderer::GetInstance()->BeginScene();

	CSceneManager::GetInstance()->Render(NULL, dt);

	Renderer::GetInstance()->Present();
}