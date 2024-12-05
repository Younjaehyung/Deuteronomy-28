#include "Gameintro.h"
#include "Time.h"
void Gameintro::Update ( )
{
    if ( status == 0 ) {
        auto carpos = car->SetPos ( );
        carpos = {carpos.x+Time::DeltaTime ( )*1.4 ,carpos.y,carpos.z + Time::DeltaTime ( ) * 35 };
        car->SetPos ( carpos );
    }
    else if ( status == 1 ) {

    }
   

}

void Gameintro::Render ( )
{
    
    if ( status == 0 ) {
        //glDisable(GL_DEPTH_TEST);

        m_camerauiProgram->Use ( );
        m_camerauiProgram->SetUniform ( "transform" , mapCamera->GetTransform ( ) * glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 (200.0f , 100.0f , 100.0f ) ) );
        MainUITEXTURE->Bind ( );
        m_camerauiProgram->SetUniform ( "tex" , 0 );
        
        // 블렌딩 활성화
        

        // 캠코더 UI 렌더링
        m_plane->Draw ( m_camerauiProgram.get ( ) );
        //glEnable ( GL_DEPTH_TEST );
        // 블렌딩 비활성화 (다른 렌더링에 영향 없도록)
        
        m_simpleProgram->Use ( );
        m_simpleProgram->SetUniform ( "transform" , mapCamera ->GetTransform()* glm::translate(glm::mat4(1.0f ) , car->GetPos ( ) )* glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( 5.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) )* glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( 90.0f ) , glm::vec3 ( -1.0f , 0.0f , 0.0f ) ) *glm::scale(glm::mat4(1.0f),glm::vec3(0.05f)) );
        m_simpleProgram->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , car->GetPos ( ) )* glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( 5.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) ) * glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians(90.0f),glm::vec3(-1.0f,0.0f,0.0f )) *glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 0.05f ) ) );
        m_simpleProgram->SetUniform ( "viewPos" , mapCamera->GetPos() );
        m_car->Draw ( m_simpleProgram.get ( ) );

        std::cout << "나는 정왕의 인트로 오승원이다" << std::endl;



    }
    else if ( status == 1 ) {


    }
}

bool Gameintro::Initialize ( )
{
    m_plane = Mesh::CreatePlane ( );
    auto MainUI = Image::Load ( "./model/UI/Main.png" , true );
    MainUITEXTURE = Texture::CreateFromImage ( MainUI.get ( ) );

    m_car = Model::Load ( "./model/Car.glb" );
    car->SetPos ( glm::vec3(0.f , -4.0f , -50.0f) );

    mapCamera = new Camera;
    mapCamera->SetCamera ( glm::vec3 ( 0.0f , 0.0f , 149.0f ), glm::vec3 ( 0.0f , 0.0f , 0.0f ),glm::vec3(0.0f,1.0f,0.0f));

    m_simpleProgram = Program::Create ( "./shader/normal.vs" , "./shader/normal.fs" );
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

