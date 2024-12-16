#include "Gamestart.h"
#include "Time.h"
#include "Sound.h"
void Gamestart::Update ( )
{
    if ( soundToggle == 0 ) {
        SoundManager::getInstance ( ).GetSoundID ( "Intro" )->ReplaySound ( 0.2 );
        soundToggle = 1;

    }
}

void Gamestart::Render (  )
{
    glDisable ( GL_DEPTH_TEST );

    m_camerauiProgram->Use ( );
    m_camerauiProgram->SetUniform ( "transform" , glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.0f , 2.0f , 1.0f ) ) );
    MainUITEXTURE->Bind ( );
    //if ( startTime <= 1.0f ) {
    //    startTime += Time::DeltaTime ( ) * 1.0f;
    //    MainStartTEXTURE->Bind ( );
    //}
    //else if ( startTime > 1.0f && startTime <= 2.0f ) {
    //    startTime += Time::DeltaTime ( ) * 1.0f;
    //}
    //else {
    //    startTime = 0.0f;
    //}

    m_camerauiProgram->SetUniform ( "tex" , 0 );

    // 블렌딩 활성화
    glEnable ( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

    // 캠코더 UI 렌더링
    m_plane->Draw ( m_camerauiProgram.get ( ) );

    // 블렌딩 비활성화 (다른 렌더링에 영향 없도록)
    glDisable ( GL_BLEND );

    glEnable ( GL_DEPTH_TEST );
}

bool Gamestart::Initialize ( )
{
	m_plane = Mesh::CreatePlane ( );
    auto MainUI = Image::Load ( "./model/UI/Title.png" , true );
    MainUITEXTURE = Texture::CreateFromImage ( MainUI.get ( ) );
    MainUI = Image::Load ( "./model/UI/TitleStart.png" , true );
    MainStartTEXTURE = Texture::CreateFromImage ( MainUI.get ( ) );
    
    m_simpleProgram = Program::Create ( "./shader/simple.vs" , "./shader/simple.fs" );
    if ( !m_simpleProgram ) {
        std::cerr << "program UserSetError id : " << m_simpleProgram->Get ( ) << std::endl;
        return false;


    }

    m_program = Program::Create ( "./shader/lighting.vs" , "./shader/lighting.fs" );
    if ( !m_program ) {
        std::cerr << "program UserSetError id : " << m_program->Get ( ) << std::endl;
        return false;


    }

    m_simpleAnimationProgram = Program::Create ( "./shader/simple_animation.vs" , "./shader/simple_animation.fs" );
    if ( !m_simpleAnimationProgram ) {
        std::cerr << "program UserSetError id : " << m_simpleAnimationProgram->Get ( ) << std::endl;
        return false;


    }

    m_camerauiProgram = Program::Create ( "./shader/cameraUI.vs" , "./shader/cameraUI.fs" );
    if ( !m_camerauiProgram ) {
        std::cerr << "program UserSetError id : " << m_camerauiProgram->Get ( ) << std::endl;
        return false;


    }



	return true;
}

