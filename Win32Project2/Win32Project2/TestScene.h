#pragma once

#include "Scene.h"


#include "Shader.h"

#include <glm/glm.hpp>

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
			//float _r, _g, _b;
			//float _nx, _ny, _nz;
		};
		float _a[3];

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

		//void SetColor( float r, float g, float b )
		//{
		//	_r = r, _g = g, _b = b;
		//}
	}			_triangle[3], _color[3];
	unsigned	_vertexBufferObject[2];

	unsigned	_vertexBufferObject2;
	unsigned	_indexBufferObject;

	unsigned	_vertexArrayID[2];

	glm::mat4 projectionMatrix;

	CShader vsh, fsh;
	CShaderProgram prog;

	glm::vec3 _heightMap[16];
};