#include "GameManager.h"
#include "Deathmap.h"
#include "Gamestart.h"
#include "Gameintro.h"
#include "context.h"
#include "Lifemap.h"
#include "gameover.h"

void GameManager::Update ( )
{
	Scenes[ static_cast< int >( mode ) ]->Update ( );

}

void GameManager::Initialize ( )
{
	input::Initialize ( );
	Time::Initailize ( );
	SoundManager::getInstance ( ).Initialize ( );

	
	Scene* startmode = new Gamestart;
	Scenes.push_back ( startmode );

	Scene* intromode = new Gameintro;
	Scenes.push_back ( intromode );

	ContextUPtr playmode = Context::Create ( );
	Scenes.push_back( playmode.get ( ) );

	Death = new Deathmap;
	

	Life = new Lifemap;
	
	Scenes.push_back ( overmode );


	Scene* endmode = new gameover;
	Scenes.push_back ( endmode );

	//Scenes[ static_cast< int >( mode ) ]->Initialize ( );

}
void GameManager::ProcessInput ( GLFWwindow* window )
{
	Scenes[ static_cast< int >( mode ) ]->ProcessInput ( window );
}

void GameManager::FixedUpdate ( )
{
}

void GameManager::Render ( )
{

	Scenes[static_cast<int>(mode)]->Render ( );

}

void GameManager::GameLogic ( ) {
	Scene* _scene = Scenes[ static_cast< int >( mode ) ];
	
		
		
		if ( status == Status::running ) {
			if ( _scene->Check ( ) ) {
				EndingNum = _scene->Check ( );
				status = Status::exit;
			}
		}
		if ( status == Status::exit ) {
			status = Status::start;

			mode = static_cast< gamemode >( static_cast< int >( mode ) + 1 );

		}
		if ( status == Status::start ) {
			_scene->Initialize ( );
			if ( mode == gamemode::Gameover ) {
				overmode = EndingNum == 1 ? Death : Life;
				EndingNum = 0;
			}
			status = Status::running;
		}


		if ( static_cast< int >( mode ) == static_cast< int >( gamemode::Max ) ) {
			mode = static_cast< gamemode >( 0 );
		}
		
	
}

void GameManager::MouseButton ( int button , int action , double x , double y )
{
	Scenes[ static_cast< int >( mode ) ]->MouseButton ( button, action,x,y );

}

void GameManager::Reshape ( int width , int height ) {

	m_width = width;
	m_height = height;
	glViewport ( 0 , 0 , m_width , m_height );

	if ( m_width <= 1 ) {
		m_width = 1;
	}
	if ( m_height <= 1 ) {
		m_height = 1;
	}

	Scenes[ static_cast< int >( mode ) ]->Reshape ( m_width , m_height );
}