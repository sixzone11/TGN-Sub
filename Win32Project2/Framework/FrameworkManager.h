#pragma once

#include <string>
#include "Macro.h"

#include "Application.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "Shader.h"

class FrameworkManager
{
public:
	FrameworkManager(void);
	~FrameworkManager(void);


public:
	SINGLETON_DEFINE(FrameworkManager)


public:
	void Update(float dt);
};