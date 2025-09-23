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
	std::cout << "=================================================================================================" << std::endl;

	std::cout << "d8888b. " << std::endl;
	std::cout << "88  `8D " << std::endl;
	std::cout << "88   88 " << std::endl;
	std::cout << "88   88 " << std::endl;
	std::cout << "88  .8D " << std::endl;
	std::cout << "Y8888D' "<< std::endl;

	std::cout << "=================================================================================================" << std::endl;
	

	//LoadingScene ( );

	SoundManager::getInstance ( ).Initialize ( );
	system ( "cls" );
	std::cout << "=================================================================================================" << std::endl;
	std::cout << "d8888b. d88888b db    db d888888b " << std::endl;
	std::cout << "88  `8D 88'     88    88 `~~88~~' " << std::endl;
	std::cout << "88   88 88ooooo 88    88    88	" << std::endl;
	std::cout << "88   88 88~~~~~ 88    88    88	" << std::endl;
	std::cout << "88  .8D 88.     88b  d88    88	" << std::endl;
	std::cout << "Y8888D' Y88888P ~Y8888P'    YP	" << std::endl;
	std::cout << "=================================================================================================" << std::endl;
	

	
	Scene* startmode = new Gamestart;
	Scenes.push_back ( startmode );



	Scene* intromode = new Gameintro;
	Scenes.push_back ( intromode );
	system ( "cls" );
	std::cout << "=================================================================================================" << std::endl;
	std::cout << "d8888b. d88888b db    db d888888b d88888b d8888b.	" << std::endl;
	std::cout << "88  `8D 88'     88    88 `~~88~~' 88'     88  `8D	" << std::endl;
	std::cout << "88   88 88ooooo 88    88    88    88ooooo 88oobY'	" << std::endl;
	std::cout << "88   88 88~~~~~ 88    88    88    88~~~~~ 88`8b	" << std::endl;
	std::cout << "88  .8D 88.     88b  d88    88    88.     88 `88.	" << std::endl;
	std::cout << "Y8888D' Y88888P ~Y8888P'    YP    Y88888P 88   YD	" << std::endl;
	std::cout << "=================================================================================================" << std::endl;

	

	Scene* playmode = new Context;
	Scenes.push_back( playmode );

	system ( "cls" );
	std::cout << "=================================================================================================" << std::endl;
	std::cout << "d8888b. d88888b db    db d888888b d88888b d8888b.  .d88b.  d8b   db " << std::endl;
	std::cout << "88  `8D 88'     88    88 `~~88~~' 88'     88  `8D .8P  Y8. 888o  88 " << std::endl;
	std::cout << "88   88 88ooooo 88    88    88    88ooooo 88oobY' 88    88 88V8o 88 " << std::endl;
	std::cout << "88   88 88~~~~~ 88    88    88    88~~~~~ 88`8b   88    88 88 V8o88 " << std::endl;
	std::cout << "88  .8D 88.     88b  d88    88    88.     88 `88. `8b  d8' 88  V888 " << std::endl;
	std::cout << "Y8888D' Y88888P ~Y8888P'    YP    Y88888P 88   YD  `Y88P'  VP   V8P " << std::endl;
	std::cout << "=================================================================================================" << std::endl;

	overmode = new Scene;

	system ( "cls" );
	std::cout << "=================================================================================================" << std::endl;
	std::cout << "d8888b. d88888b db    db d888888b d88888b d8888b.  .d88b.  d8b   db  .d88b.  .88b  d88.		   " << std::endl;
	std::cout << "88  `8D 88'     88    88 `~~88~~' 88'     88  `8D .8P  Y8. 888o  88 .8P  Y8. 88'YbdP`88		   " << std::endl;
	std::cout << "88   88 88ooooo 88    88    88    88ooooo 88oobY' 88    88 88V8o 88 88    88 88  88  88		   " << std::endl;
	std::cout << "88   88 88~~~~~ 88    88    88    88~~~~~ 88`8b   88    88 88 V8o88 88    88 88  88  88		   " << std::endl;
	std::cout << "88  .8D 88.     88b  d88    88    88.     88 `88. `8b  d8' 88  V888 `8b  d8' 88  88  88		   " << std::endl;
	std::cout << "Y8888D' Y88888P ~Y8888P'    YP    Y88888P 88   YD  `Y88P'  VP   V8P  `Y88P'  YP  YP  YP		   " << std::endl;
	std::cout << "=================================================================================================" << std::endl;


	Death = new Deathmap;
	Life = new Lifemap;
	
	Scenes.push_back ( overmode );
	Scenes.push_back ( Death );
	Scenes.push_back ( Life );
	Scene* endmode = new gameover;
	Scenes.push_back ( endmode );
	
	//Scenes[ static_cast< int >( mode ) ]->Initialize ( );
	system ( "cls" );
	std::cout << "=================================================================================================" << std::endl;
	std::cout << "d8888b. d88888b db    db d888888b d88888b d8888b.  .d88b.  d8b   db  .d88b.  .88b  d88. db    db " << std::endl;
	std::cout << "88  `8D 88'     88    88 `~~88~~' 88'     88  `8D .8P  Y8. 888o  88 .8P  Y8. 88'YbdP`88 `8b  d8' " << std::endl;
	std::cout << "88   88 88ooooo 88    88    88    88ooooo 88oobY' 88    88 88V8o 88 88    88 88  88  88  `8bd8'  " << std::endl;
	std::cout << "88   88 88~~~~~ 88    88    88    88~~~~~ 88`8b   88    88 88 V8o88 88    88 88  88  88    88    " << std::endl;
	std::cout << "88  .8D 88.     88b  d88    88    88.     88 `88. `8b  d8' 88  V888 `8b  d8' 88  88  88    88    " << std::endl;
	std::cout << "Y8888D' Y88888P ~Y8888P'    YP    Y88888P 88   YD  `Y88P'  VP   V8P  `Y88P'  YP  YP  YP    YP    " << std::endl;
	std::cout << "=================================================================================================" << std::endl;

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

			
				if ( EndingNum == 1 ) {
					overmode = Death;
					mode = static_cast< gamemode >( static_cast< int >( mode ) + 1 );

				}
				else {
					mode = static_cast< gamemode >( static_cast< int >( mode ) + 2 );

				}
				EndingNum = 0;
			}
			if ( mode == gamemode::Gameend ) {
				EndingNum == 0;
				mode = static_cast< gamemode >( static_cast< int >( gamemode::play ) );
				CollisionManager::getInstance ( ).ResetCollision ( );
				CameraManager::getInstance ( ).ResetCamera ( );
				LightManager::getInstance ( ).ResetLight ( );
				Scenes[ static_cast< int >( gamemode::play ) ] = new Context;
				Scenes[ static_cast< int >( gamemode::GameDeath ) ] = new Deathmap;
				SoundManager::getInstance ( ).StopAllChannels ( );
				SoundManager::getInstance ( ).GetSoundID ( "Ambient" )->ReplaySound ( );
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

	Scenes[ static_cast< int >( mode ) ]->Reshape ( m_width , m_height );
	
}