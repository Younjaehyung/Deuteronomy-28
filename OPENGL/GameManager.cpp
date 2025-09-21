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

	overmode = new Scene;
	Death = new Deathmap;
	Life = new Lifemap;
	
	Scenes.push_back ( overmode );
	Scenes.push_back ( Death );
	Scenes.push_back ( Life );
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
	
		
		
		if ( status == Status::running ) {
			if ( _scene->Check ( ) ) {
				EndingNum = _scene->Check ( );
				
				status = Status::exit;
			}
		}
		if ( status == Status::exit ) {
			status = Status::start;
			SoundManager::getInstance ( ).StopAllChannels ( );
			

			if ( mode == gamemode::GameDeath ) {

				mode = gamemode::Gameend;
			}
			else {
				mode = static_cast< gamemode >( static_cast< int >( mode ) + 1 );
			}


		}
		if ( status == Status::start ) {
			SoundManager::getInstance ( ).GetSoundID ( "Ambient" )->ReplaySound ( 0.6f );
			//_scene->Reset ( );
			if ( mode == gamemode::Gameover ) {
				std::cout <<"나는 정왕 종결자 오승원이다" << EndingNum << std::endl;
			
				if ( EndingNum == 1 ) {
					overmode = Death;
					mode = static_cast< gamemode >( static_cast< int >( mode ) + 1 );
					std::cout << "나는 죽었ㅇ다" << EndingNum << std::endl;
				}
				else {
					mode = static_cast< gamemode >( static_cast< int >( mode ) + 2 );
					std::cout << "나는 살았ㅇ다" << EndingNum << std::endl;
				}
				EndingNum = 0;
			}
			if ( mode == gamemode::Gameend) {
				EndingNum == 0;
				mode = static_cast< gamemode >( static_cast< int >( gamemode::play ) );
				CollisionManager::getInstance ( ).ResetCollision ( );
				CameraManager::getInstance ( ).ResetCamera ( );
				LightManager::getInstance ( ).ResetLight ( );
				Scenes[ static_cast< int >( gamemode::play ) ] = new Context;
				Scenes[ static_cast< int >( gamemode::GameDeath ) ] = new Deathmap;
				SoundManager::getInstance ( ).StopAllChannels ( );
				SoundManager::getInstance ( ).GetSoundID ( "Ambient" )->ReplaySound();
				std::cout << "나는 불꽃페미니스트전사 오승원이다!!" << std::endl;
			}

			Reshape ( m_width , m_height );

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