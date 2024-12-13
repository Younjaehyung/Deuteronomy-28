#include "Lifemap.h"
#include "LightManager.h"
#include "Time.h"

void Lifemap::Update ( )
{
    animator->UpdateAnimation ( Time::DeltaTime ( ) );

    mapCamera->Update ( );
}

void Lifemap::Render ( )
{

    std::cout << "나는 정왕의 데스신 오승원이다." << std::endl;
    auto _cameraTransform = mapCamera->GetProjection ( ) * mapCamera->GetView ( );

    m_simpleProgram->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) );
    m_simpleProgram->SetUniform ( "transform" , _cameraTransform * glm::translate ( glm::mat4 ( 1.0f ) , Pos ) );


    //LightManager::getInstance ( ).GetLightSetting ( m_simpleProgram.get() );
    m_map->Draw ( m_simpleProgram.get ( ) );

    const auto& transforms = animator->GetFinalBoneMatrices ( );
    m_simpleAnimationProgram->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) );
    m_simpleAnimationProgram->SetUniform ( "transform" , _cameraTransform * glm::translate ( glm::mat4 ( 1.0f ) , Pos ) );
    UBO->Bind ( m_simpleAnimationProgram->Get ( ) , "Bones" );
    UBO->UpdateBoneMatrices ( transforms );

    // LightManager::getInstance ( ).GetLightSetting ( m_simpleAnimationProgram.get ( ) );
     //m_player->Draw ( m_simpleAnimationProgram.get ( ) );
    m_monster->Draw ( m_simpleAnimationProgram.get ( ) );

}

bool Lifemap::Initialize ( )
{
    std::cerr << "Life MAP start " << std::endl;


	return false;
}

