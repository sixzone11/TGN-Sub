#pragma once

#include "Scene.h"

class TestScene : public CScene
{
public:
	TestScene(void);
	~TestScene(void);


public:
	virtual void Initialize(void* context);
	virtual void Update(void* context, float dt);
	virtual void Render(void* context, float dt);
	virtual void Release(void* context);


public:
	virtual void HardwereResponse(void* context, const CInput* input);
	

private:
	float		_cameraZ;
	float		_cameraAngle;
};