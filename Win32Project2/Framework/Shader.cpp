#include "Shader.h"

#include "Renderer.h"
#include "PlatformBase.h"

#include <vector>


CShader::CShader(void) : _loaded( false )
{
}


CShader::~CShader(void)
{
	DeleteShader();
}


bool CShader::LoadShader( std::string filename, int type )
{
	FILE* fp = fopen( filename.c_str(), "r" );
	if( fp == NULL ) return false;

	char textLine[256];
	std::string source = "";

	while( fgets( textLine, 256, fp ) )
		source.append( textLine );
	fclose( fp );


	_shaderID = glCreateShader( type );

	const char* sourceRef = source.c_str();
	glShaderSource( _shaderID, 1, &sourceRef, NULL );
	glCompileShader( _shaderID );


	int status;
	glGetShaderiv( _shaderID, GL_COMPILE_STATUS, &status );

	if( status == GL_FALSE )
	{
		int infoLogLen;
		std::vector<char> errMsg;

		glGetShaderiv( _shaderID, GL_INFO_LOG_LENGTH, &infoLogLen );
		glGetShaderInfoLog( _shaderID, infoLogLen, NULL, &errMsg[0] );

		LOG( "%s", &errMsg[0] );
		_shaderID = NULL;

		return false;
	}

	_type = type;
	_loaded = true;

	return true;
}

void CShader::DeleteShader()
{
	if( IsLoaded() == false ) return;

	_loaded = false;
	glDeleteShader( _shaderID );
}


/*
	Shader Program class
*/
CShaderProgram::CShaderProgram() : _linked( false )
{
}

CShaderProgram::~CShaderProgram()
{
	DeleteProgram();
}

void CShaderProgram::CreateProgram()
{
	_programID = glCreateProgram();
}

bool CShaderProgram::AddShaderToProgram( CShader* shader )
{
	if( shader->IsLoaded() == false ) return false;

	glAttachShader( _programID, shader->GetShaderID() );

	return true;
}

bool CShaderProgram::LinkProgram()
{
	glLinkProgram( _programID );

	int status;
	glGetProgramiv( _programID, GL_LINK_STATUS, &status );

	return _linked = ( status == GL_TRUE );
}

void CShaderProgram::DeleteProgram()
{
	if( IsLinked() == false ) return;

	_linked = false;
	glDeleteProgram( _programID );
}

void CShaderProgram::UseProgram()
{
	if( IsLinked() ) glUseProgram( _programID );
}