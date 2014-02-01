
#include <string>
#include "Macro.h"

#include "Shader.h"

#include <vector>


CShader::CShader(void)
{
}


CShader::~CShader(void)
{
}


bool CShader::LoadShader( std::string filename, int type )
{
	FILE* fp = fopen( filename.c_str(), "r" );
	if( fp == NULL ) return false;

	std::vector< std::string > lines;
	char textLine[256];

	while( fgets( textLine, 256, fp ) )
		lines.push_back( textLine );
	fclose( fp );

	


	return true;
}