#pragma once

#include "Input.h"

class CScene
{
public:
	CScene(void) {}
	~CScene(void) {}


public:
	virtual void Initialize(void* context) {}
	virtual void Update(void* context, float dt) {}
	virtual void Render(void* context, float dt) {}
	virtual void Release(void* context) {}
	
public:
	virtual void HardwereResponse(void* context, const CInput* input) {}
};