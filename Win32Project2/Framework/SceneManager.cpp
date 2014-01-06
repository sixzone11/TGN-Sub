#include "SceneManager.h"

#include "FrameworkManager.h"

CSceneManager::CSceneManager( void )
	: _mainScene(NULL)
{
}


CSceneManager::~CSceneManager( void )
{
	std::map<std::string, CScene*>::iterator iter;

	for( iter = _sceneDictionary.begin() ; iter != _sceneDictionary.end() ; ++iter)
	{
		delete (iter->second);
	}

	_sceneDictionary.clear();
}

void CSceneManager::AddScene( CScene* scene, std::string& key, bool isMain )
{
	_sceneDictionary[key] = scene;
	
	if( isMain || _mainScene == NULL )
	{
		_mainScene = scene;
	}
}

void CSceneManager::Update( void* context, float dt )
{
	_mainScene->Update(context, dt);
}

void CSceneManager::Render( void* context, float dt )
{
	_mainScene->Render(context, dt);
}

void CSceneManager::HardwereResponse( void* context, const CInput* input )
{
	_mainScene->HardwereResponse( context, input );
}