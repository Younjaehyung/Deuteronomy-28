#include "GameManager.h"

void GameManager::Update ( )
{
	
	playing_Scene->Update ( );
	
	
}

void GameManager::AddScene ( )
{
	Scenes.push_back ( addscene );
}

void GameManager::Initialize ( )
{
	Add

	for ( auto _Scenes : Scenes ) {
		_Scenes->Initialize ( );
	}

	playing_Scene = Scenes[ playing_index ];
}

void GameManager::FixedUpdate ( )
{
	playing_Scene->FixedUpdate ( );
}

void GameManager::Render ( )
{
	playing_Scene->Render ( );

}
