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
	void ShaderInitialize();
	

private:
	float		_cameraZ;
	float		_cameraAngle;


private:
	unsigned	_programHandle;

	union
	{
		struct
		{
			float _x, _y, _z;
			//float _nx, _ny, _nz;
		};
		float _a[3]; //6];

		void Set(float x = 0.f, float y = 0.f, float z = 0.f)//, float nx = 0.f, float ny = 0.f, float nz = 0.f)
		{
			_x = x, _y = y, _z = z;
			//_nx = nx, _ny = ny, _nz = nz;
		}
		void Set(float a[6])
		{
			_a[0] = a[0], _a[1] = a[1], _a[2] = a[2];
			//_a[3] = a[3], _a[4] = a[4], _a[5] = a[5];
		}
	}			_triangle[3], _quad[4];
	unsigned	_vertexBufferObject[2];
};