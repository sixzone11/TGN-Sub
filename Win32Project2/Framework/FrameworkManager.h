#pragma once

#include "Application.h"
#include "SceneManager.h"
#include "Renderer.h"

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