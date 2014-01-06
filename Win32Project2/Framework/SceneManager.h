#pragma once

#include "Scene.h"

#include <map>
#include <string>

#include "Macro.h"

class CSceneManager
{
public:
	CSceneManager( void );
	~CSceneManager( void );


public:
	SINGLETON_DEFINE(CSceneManager)


public:
	inline void	AddScene( CScene* scene, const char* key, bool isMain = false )
	{
		AddScene(scene, std::string(key), isMain);
	}
	void		AddScene( CScene* scene, std::string& key, bool isMain = false );


public:
	void		SetScene( CScene* scene );


public:
	void		Update( void* context, float dt);
	void		Render( void* context, float dt);
	void		HardwereResponse( void* context, const CInput* input );


private:
	std::map<std::string, CScene*>	_sceneDictionary;
	CScene*							_mainScene;

	CScene*							_nextScene;
	CScene*							_prevScene;
};

