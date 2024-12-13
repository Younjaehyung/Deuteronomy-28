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

void GameManager::LoadingScene ( ) {
	auto m_plane = Mesh::CreatePlane ( );
	m_LoadingScreenProgram->Use ( );
	m_LoadingScreenProgram->SetUniform ( "transform" , glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.0f , 2.0f , 1.0f ) ) );
	LoadingScreen->Bind ( );
	m_LoadingScreenProgram->SetUniform ( "tex" , 0 );
	m_plane->Draw ( m_LoadingScreenProgram.get ( ) );
}

void GameManager::Initialize ( )
{
	input::Initialize ( );
	Time::Initailize ( );

	
	//LoadingScene ( );

	SoundManager::getInstance ( ).Initialize ( );

	
	Scene* startmode = new Gamestart;
	Scenes.push_back ( startmode );

	Scene* intromode = new Gameintro;
	Scenes.push_back ( intromode );

	Scene* playmode = new Context;
	Scenes.push_back( playmode );

	Death = new Deathmap;
	Life = new Lifemap;
	
	Scenes.push_back ( Death );


	Scene* endmode = new gameover;
	Scenes.push_back ( endmode );
	
	//Scenes[ static_cast< int >( mode ) ]->Initialize ( );

}
void GameManager::ProcessInput ( GLFWwindow* window )
{
	Time::Update ( );
	input::Update ( window );
	Scenes[ static_cast< int >( mode ) ]->ProcessInput ( window );
}

void GameManager::FixedUpdate ( )
{
}

void GameManager::Render ( )
{
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT ); //GL_DEPTH_BUFFER_BIT : DEPTH Buffer clear 세팅
	Scenes[static_cast<int>(mode)]->Render ( );

}

void GameManager::GameLogic ( ) {
	Scene* _scene = Scenes[ static_cast< int >( mode ) ];
	std::cout << "나는 정왕의 데스신 오승원이다." << std::endl;
		
		
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
			
			//_scene->Reset ( );
			Reshape ( m_width , m_height );
			if ( mode == gamemode::Gameover ) {
				std::cout <<"나는 정왕 종결자 오승원이다" << EndingNum << std::endl;
				overmode =  (EndingNum ==0 ) ? Death : Life;
				
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

	//if ( m_width <= 1 ) {
	//	m_width = 1;
	//}
	//if ( m_height <= 1 ) {
	//	m_height = 1;
	//}
	//
	std::cout << Scenes.size() << std::endl;
	Scenes[ static_cast< int >( mode ) ]->Reshape ( m_width , m_height );
	
}