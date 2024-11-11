#include "GameManager.h"
#include "Player.h"


void GameManager::Update ( )
{
	for ( auto _Gameobjects : Gameobjects ) {


		_Gameobjects->Update ( );

	}
	
	
}


void GameManager::Initialize ( )
{
	Player* player = new Player("player" );
	Gameobjects.push_back ( player );


	for ( auto _Gameobjects : Gameobjects ) {


		_Gameobjects->Initialize ( );

	}
}

void GameManager::Input ( GLFWwindow* window )
{
	for ( auto _Gameobjects : Gameobjects ) {


		_Gameobjects->Input ( window );

	}
}

void GameManager::FixedUpdate ( )
{
	for ( auto _Gameobjects : Gameobjects ) {


		_Gameobjects->FixedUpdate ( );

	}
}

void GameManager::Render ( )
{
	
	for ( auto _Gameobjects : Gameobjects ) {


		_Gameobjects->Render ( );

	}
}
