#pragma once

class CShader
{
public:
	CShader();
	~CShader();


public:
	bool			LoadShader( std::string filename, int type );
	void			DeleteShader();



private:
	int				_type;


public:
	DEFINE_GET_SET_ACCESSOR(		ShaderID, unsigned, _shaderID );
	DEFINE_IS_SET_ACCESSOR(			Loaded, bool, _loaded );
};

