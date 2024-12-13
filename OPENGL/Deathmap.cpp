#include "Deathmap.h"
#include "LightManager.h"
#include "Time.h"
void Deathmap::Update ( )
{
    animator->UpdateAnimation ( Time::DeltaTime ( ) );

    mapCamera->Update ( );

}

void Deathmap::Render ()
{
    glClearColor ( 0.1f , 0.2f , 0.1f , 1.0f );
    std::cout << "나는 정왕의 데스신 오승원이다." << std::endl;
    auto _cameraTransform = mapCamera->GetProjection ( ) * mapCamera->GetView ( );
    m_simpleProgram->Use ( );
    m_simpleProgram->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) );
    m_simpleProgram->SetUniform ( "transform" , _cameraTransform * glm::translate ( glm::mat4 ( 1.0f ) , Pos ) );
    m_simpleProgram->SetUniform ( "light.direction" , light.direction );
    m_simpleProgram->SetUniform ( "light.attenuation" , light.attenuation );
    m_simpleProgram->SetUniform ( "light.cutoff" , light.cutoff );
    m_simpleProgram->SetUniform ( "light.position" , light.position );
    m_simpleProgram->SetUniform ( "light.ambient" , light.ambient );
    m_simpleProgram->SetUniform ( "light.diffuse" , light.diffuse );
    m_simpleProgram->SetUniform ( "light.specular" , light.specular );
    m_simpleProgram->SetUniform ( "viewPos" , _cameraTransform * glm::translate ( glm::mat4 ( 1.0f ) , Pos ) );
    m_simpleProgram->SetUniform ( "blinn" , _cameraTransform * glm::translate ( glm::mat4 ( 1.0f ) , Pos ) );
   
	//LightManager::getInstance ( ).GetLightSetting ( m_simpleProgram.get() );
    m_map->Draw ( m_simpleProgram.get ( ) );

    const auto& transforms = animator->GetFinalBoneMatrices ( );
    m_simpleAnimationProgram->Use ( );
    m_simpleAnimationProgram->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) );
    m_simpleAnimationProgram->SetUniform ( "transform" , _cameraTransform * glm::translate ( glm::mat4 ( 1.0f ) , Pos )  );
    UBO->Bind ( m_simpleAnimationProgram->Get ( ) , "Bones" );
    UBO->UpdateBoneMatrices ( transforms );

   // LightManager::getInstance ( ).GetLightSetting ( m_simpleAnimationProgram.get ( ) );
    //m_player->Draw ( m_simpleAnimationProgram.get ( ) );
    m_monster->Draw ( m_simpleAnimationProgram.get ( ) );


}

bool Deathmap::Initialize ()
{
    std::cerr << "DEATH MAP start " << std::endl;
    


    return true;
}

