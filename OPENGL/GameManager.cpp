#include "GameManager.h"
#include "PlayScene1.h"

void GameManager::Update ( )
{
	
	for ( auto& _Scene : Scenes ) {
		_Scene->Update ( );
	}

}

void GameManager::Initialize ( )
{
	input::Initialize ( );

	Scene* Scene1 = new PlayScene1;
	AddScene ( Scene1 );

	for ( auto& _Scene : Scenes ) {
		_Scene->Initialize ( );
	}
}

void GameManager::AddScene (Scene* _scene) {
	Scenes.push_back ( _scene );
}

void GameManager::FixedUpdate ( )
{
	for ( auto& _Scene : Scenes ) {
		_Scene->FixedUpdate ( );
	}
}

void GameManager::Render ( )
{
	
	for ( auto& _Scene : Scenes ) {
		_Scene->Render ( );
	}
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT ); //GL_DEPTH_BUFFER_BIT : DEPTH Buffer clear 세팅
	glEnable ( GL_DEPTH_TEST ); // DEPTH Buffer 사용 설정
}
