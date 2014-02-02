#pragma once

#include <string>
#include "Macro.h"

class CShader
{
public:
	CShader();
	~CShader();


public:
	bool			LoadShader( std::string filename, int type );
	void			DeleteShader();


public:
	GET_ACCESSOR(	ShaderID, unsigned, _shaderID );
	IS_ACCESSOR(	Loaded, bool, _loaded );
	

private:
	int				_type;
	unsigned		_shaderID;
	bool			_loaded;
};


class CShaderProgram
{
public:
	CShaderProgram();
	~CShaderProgram();


public:
	void			CreateProgram();
	void			DeleteProgram();


public:
	bool			AddShaderToProgram( CShader* shader );
	bool			LinkProgram();
	
	void			UseProgram();


public:
	GET_ACCESSOR(	ProgramID, unsigned, _programID );
	IS_ACCESSOR(	Linked, bool, _linked );


private:
	unsigned		_programID;
	bool			_linked;
};