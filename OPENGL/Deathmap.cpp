#include "Deathmap.h"
#include "LightManager.h"
#include "Time.h"
#include "Sound.h"
#include "include/glm/gtc/quaternion.hpp"

void Deathmap::Update ( )
{
    if ( attack == 0 ) {
        Manima2tor->UpdateAnimation ( Time::DeltaTime ( ) );
        attack_time += Time::DeltaTime ( );
        auto cameraPos = mapCamera->GetPos ( );
        mapCamera->GetPos ( ) = { cameraPos.x-0.2f,cameraPos.y-3.0f,cameraPos.z };
        if ( SoundToggle == 0 ) {
            SoundManager::getInstance ( ).GetSoundID ( "Player_Die" )->ReplaySound ( 1.5f );
            SoundManager::getInstance ( ).GetSoundID ( "Roar" )->ReplaySound (0.7f);
            SoundManager::getInstance ( ).GetSoundID ( "Monster_Eat" )->ReplaySound ( 0.9f );
            
            SoundToggle = 1;
        }

        if ( attack_time > 1.7f ) {
            attack = 1;
        }
    }

    else if ( attack == 1 ) {
        Panimator->UpdateAnimation ( Time::DeltaTime ( ) );
        Manimator->UpdateAnimation ( Time::DeltaTime ( ) );


        std::cout << elapsedTime / animationDuration << std::endl;

        elapsedTime += Time::DeltaTime ( );
        float t = glm::clamp ( elapsedTime / animationDuration , 0.0f , 1.0f );
        std::cout << t << std::endl;
        // 위치 보간
        glm::vec3 currentCameraPos = glm::mix ( initialCameraPos , finalCameraPos , t );
        mapCamera->GetPos ( ) = currentCameraPos;
        // 회전 보간
        glm::quat currentCameraRot = glm::slerp ( initialCameraRot , finalCameraRot , t );

        std::cout << currentCameraPos.x << currentCameraPos.x << currentCameraPos.y << currentCameraPos.z << std::endl;

        // 카메라 매트릭스 업데이트

        mapCamera->GetView ( ) = glm::lookAt (
        currentCameraPos ,                // 카메라 위치
        currentCameraPos + glm::normalize ( glm::vec3 ( DeathPos.x , currentCameraPos.y + 0.1f , DeathPos.z ) - currentCameraPos ) , // 카메라 방향
        glm::vec3 ( 0.0f , 1.0f , 0.0f ) );

        

        if ( elapsedTime >= animationDuration + 3.0f ) {
            status = 1;
            attack = 2;

            SoundManager::getInstance ( ).StopAllChannels ( );
            SoundManager::getInstance ( ).GetSoundID ( "Die" )->ReplaySound ( 0.6 );

        }
        
    }
    else if ( attack == 2 ) {
        elapsedTime += Time::DeltaTime ( );
        if ( elapsedTime >= animationDuration + 5.7f ) {
            status = 2;
        }
    }


}



void Deathmap::Render ()
{
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT ); //GL_DEPTH_BUFFER_BIT : DEPTH Buffer clear 세팅

    shadowRender ( );
    MainRender ( );

}

void Deathmap::MainRender ( )
{
    //그림자&&빛
    glViewport ( 0 , 0 , m_width , m_height );

    m_framebuffer->Bind ( );

    //glDisable ( GL_CULL_FACE );
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT ); //GL_DEPTH_BUFFER_BIT : DEPTH Buffer clear 세팅

    


    program = m_lightingProgram.get ( );
    Light_ORI lights = light->GetlightData ( );
    
    auto _cameraTransform = mapCamera->GetProjection ( ) * mapCamera->GetView ( );
    program->Use ( );
    program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.f , -1.f , -9.f ) ) * glm::scale( glm::mat4 ( 1.0f ) ,glm::vec3(0.5f))*glm::mat4 ( 1.0f ) );
    program->SetUniform ( "transform" , _cameraTransform * glm::translate ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.f,-1.f,-9.f ) ) *glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 0.5f ) ) );
    program->SetUniform ( "lights[0].directional" , 0 );
    program->SetUniform ( "lights[0].direction" , lights.direction );
    program->SetUniform ( "lights[0].attenuation" , lights.attenuation );
    program->SetUniform ( "lights[0].cutoff" , lights.cutoff );
    program->SetUniform ( "lights[0].position" , lights.position );
    program->SetUniform ( "lights[0].ambient" , lights.ambient );
    program->SetUniform ( "lights[0].diffuse" , lights.diffuse );
    program->SetUniform ( "lights[0].specular" , lights.specular );
    program->SetUniform ( "viewPos" , mapCamera->GetPos ( ) );
    program->SetUniform ( "blinn" , 1 );
    program->SetUniform ( "numLights" , 1 );

    program->SetUniform ( "lightTransform[0]" , light->GetlightProjection ( ) * light->GetlightView ( ) );

    glActiveTexture ( GL_TEXTURE0 + 5 );
    light->GetlightShadowMap ( )->GetShadowMap ( )->Bind ( );
    program->SetUniform ( "shadowMaps[0]" , 5 );
    

    //m_map->Draw ( program );

    program->SetUniform ( "transform" , _cameraTransform * glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( 90.0f ) , glm::vec3 ( 1.0f , 0.0f , 0.0f ) )
    * glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 100.0f , 100.0f , 100.0f ) ) );
    ground->Draw ( program );


    if ( attack == 0 ) {
        const auto& Mtransforms = Manima2tor->GetFinalBoneMatrices ( );
        program = m_AnimationProgram.get ( );
        program->Use ( );
        program->SetUniform ( "modelTransform" , glm::translate(glm::mat4 ( 1.0f ),glm::vec3(1.0f,-1.0f,-9.0f)) );
        program->SetUniform ( "transform" , _cameraTransform * glm::translate ( glm::mat4 ( 1.0f ) , glm::vec3 ( 1.0f , -1.0f , -9.0f ) ) );
        program->SetUniform ( "lights[0].directional" , 0 );
        program->SetUniform ( "lights[0].direction" , lights.direction );
        program->SetUniform ( "lights[0].attenuation" , lights.attenuation );
        program->SetUniform ( "lights[0].cutoff" , lights.cutoff );
        program->SetUniform ( "lights[0].position" , lights.position );
        program->SetUniform ( "lights[0].ambient" , lights.ambient );
        program->SetUniform ( "lights[0].diffuse" , lights.diffuse );
        program->SetUniform ( "lights[0].specular" , lights.specular );
        program->SetUniform ( "viewPos" , mapCamera->GetPos ( ) );
        program->SetUniform ( "blinn" , 1 );
        program->SetUniform ( "numLights" , 1 );
        program->SetUniform ( "lightTransform[0]" , light->GetlightProjection ( ) * light->GetlightView ( ) );

        glActiveTexture ( GL_TEXTURE0 + 5 );
        light->GetlightShadowMap ( )->GetShadowMap ( )->Bind ( );
        program->SetUniform ( "shadowMaps[0]" , 5 );

        MUBO->Bind ( program->Get ( ) , "Bones" );
        MUBO->UpdateBoneMatrices ( Mtransforms );
        m_monster->Draw ( program );

    }
    else {
        const auto& Mtransforms = Manimator->GetFinalBoneMatrices ( );
        const auto& Ptransforms = Panimator->GetFinalBoneMatrices ( );


        program = m_AnimationProgram.get ( );
        program->Use ( );
        program->SetUniform ( "modelTransform" , glm::mat4 ( 1.0f ) );
        program->SetUniform ( "transform" , _cameraTransform * glm::mat4 ( 1.0f ) );
        program->SetUniform ( "lights[0].directional" , 0 );
        program->SetUniform ( "lights[0].direction" , lights.direction );
        program->SetUniform ( "lights[0].attenuation" , lights.attenuation );
        program->SetUniform ( "lights[0].cutoff" , lights.cutoff );
        program->SetUniform ( "lights[0].position" , lights.position );
        program->SetUniform ( "lights[0].ambient" , lights.ambient );
        program->SetUniform ( "lights[0].diffuse" , lights.diffuse );
        program->SetUniform ( "lights[0].specular" , lights.specular );
        program->SetUniform ( "viewPos" , mapCamera->GetPos ( ) );
        program->SetUniform ( "blinn" , 1 );
        program->SetUniform ( "numLights" , 1 );
        program->SetUniform ( "lightTransform[0]" , light->GetlightProjection ( ) * light->GetlightView ( ) );

        glActiveTexture ( GL_TEXTURE0 + 5 );
        light->GetlightShadowMap ( )->GetShadowMap ( )->Bind ( );
        program->SetUniform ( "shadowMaps[0]" , 5 );

        MUBO->Bind ( program->Get ( ) , "Bones" );
        MUBO->UpdateBoneMatrices ( Mtransforms );
        m_monster->Draw ( program );


        program = m_AnimationProgram.get ( );
        program->Use ( );
        program->SetUniform ( "modelTransform" , glm::mat4 ( 1.0f ) * glm::translate ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.0f , 0.0f , -5.0f ) ) );
        program->SetUniform ( "transform" , _cameraTransform * glm::mat4 ( 1.0f ) * glm::mat4 ( 1.0f ) * glm::translate ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.0f , 0.0f , -5.0f ) ) );
        program->SetUniform ( "lights[0].directional" , 0 );
        program->SetUniform ( "lights[0].direction" , lights.direction );
        program->SetUniform ( "lights[0].attenuation" , lights.attenuation );
        program->SetUniform ( "lights[0].cutoff" , lights.cutoff );
        program->SetUniform ( "lights[0].position" , lights.position );
        program->SetUniform ( "lights[0].ambient" , lights.ambient );
        program->SetUniform ( "lights[0].diffuse" , lights.diffuse );
        program->SetUniform ( "lights[0].specular" , lights.specular );
        program->SetUniform ( "viewPos" , mapCamera->GetPos ( ) );
        program->SetUniform ( "blinn" , 1 );
        program->SetUniform ( "numLights" , 1 );
        program->SetUniform ( "lightTransform[0]" , light->GetlightProjection ( ) * light->GetlightView ( ) );

        glActiveTexture ( GL_TEXTURE0 + 5 );
        light->GetlightShadowMap ( )->GetShadowMap ( )->Bind ( );
        program->SetUniform ( "shadowMaps[0]" , 5 );

        PUBO->Bind ( program->Get ( ) , "Bones" );
        PUBO->UpdateBoneMatrices ( Ptransforms );
        m_player->Draw ( program );

    }


    glDisable ( GL_DEPTH_TEST );

    m_cameraUIProgram->Use ( );
    m_cameraUIProgram->SetUniform ( "transform" , glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.0f , 2.0f , 1.0f ) ) );
   
   

   

   
    // 블렌딩 활성화
    glEnable ( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
    
    
    if ( status == 1 ) {
        BloodTEXTURE->Bind ( );
        m_cameraUIProgram->SetUniform ( "tex" , 0 );
        m_plane->Draw ( m_cameraUIProgram.get ( ) );
    }
    CameraUITEXTURE->Bind ( );
    m_cameraUIProgram->SetUniform ( "tex" , 0 );
    m_plane->Draw ( m_cameraUIProgram.get ( ) );
    
    // 캠코더 UI 렌더링
   

    // 블렌딩 비활성화 (다른 렌더링에 영향 없도록)
    glDisable ( GL_BLEND );

    glEnable ( GL_DEPTH_TEST );
    if ( status == 2 ) {
        DIETEXTURE->Bind ( );
        m_cameraUIProgram->SetUniform ( "tex" , 0 );
        m_plane->Draw ( m_cameraUIProgram.get ( ) );
    }

    Framebuffer::BindToDefault ( );
    m_textureProgram->Use ( );
    if ( attack == 2 ) {
        m_textureProgram->SetUniform ( "typeID" , -1 );
    }
    else {
        m_textureProgram->SetUniform ( "typeID" , 2 );
    }
    m_textureProgram->SetUniform ( "transform" ,
               glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.0f , 2.0f , 1.0f ) ) );
    m_framebuffer->GetColorAttachment ( )->Bind ( );
    m_textureProgram->SetUniform ( "tex" , 0 );

    m_textureProgram->SetUniform ( "resolution" , glm::vec2 ( 2560 , 1440 ) );
    nowTime += Time::DeltaTime ( );
    m_textureProgram->SetUniform ( "time" , nowTime );

    m_plane->Draw ( m_textureProgram.get ( ) );


}

void Deathmap::shadowRender ( )
{

    const auto& Mtransforms = Manimator->GetFinalBoneMatrices ( );
    const auto& Ptransforms = Panimator->GetFinalBoneMatrices ( );

    glClearColor ( 0.1f , 0.0f , 0.0f , 1.0f );
    glEnable ( GL_DEPTH_TEST );
    glClear ( GL_DEPTH_BUFFER_BIT );
    glEnable ( GL_CULL_FACE );
    glCullFace ( GL_FRONT_FACE );

    light->GetlightShadowMap ( )->Bind ( );
    glViewport ( 0 , 0 ,
    light->GetlightShadowMap ( )->GetShadowMap ( )->GetWidth ( ) ,
    light->GetlightShadowMap ( )->GetShadowMap ( )->GetHeight ( ) );
    glClear ( GL_DEPTH_BUFFER_BIT );

    program = m_simpleProgram.get ( );

    program->Use ( );
    program->SetUniform ( "color" , glm::vec4 ( 1.0f , 1.0f , 1.0f , 1.0f ) );
    program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.f , -1.f , -9.f ) )* glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 0.5f ) ) );
    program->SetUniform ( "transform" , light->GetlightProjection ( ) * light->GetlightView ( ) * glm::translate ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.f , -1.f , -9.f ) )* glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 0.5f ) ));


    m_map->Draw ( program );

    program = m_simpleAnimationProgram.get ( );

    program->Use ( );
    program->SetUniform ( "color" , glm::vec4 ( 1.0f ) );
    program->SetUniform ( "modelTransform" , glm::mat4 ( 1.0f )* glm::mat4 ( 1.0f )  );
    program->SetUniform ( "transform" , light->GetlightProjection ( ) * light->GetlightView ( )  );



    MUBO->Bind ( program->Get ( ) , "Bones" );
    MUBO->UpdateBoneMatrices ( Mtransforms );
    m_monster->Draw ( program );



    program = m_simpleAnimationProgram.get ( );

    program->Use ( );
    program->SetUniform ( "color" , glm::vec4 ( 1.0f ) );
    program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.0f , 0.0f , -3.0f ) ) );
    program->SetUniform ( "transform" , light->GetlightProjection ( ) * light->GetlightView ( ) * glm::translate ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.0f , 0.0f , -3.0f ) ) );

    PUBO->Bind ( program->Get ( ) , "Bones" );
    PUBO->UpdateBoneMatrices ( Ptransforms );
    m_player->Draw ( program );

    Framebuffer::BindToDefault ( );



}


bool Deathmap::Initialize ()
{
    std::cerr << "DEATH MAP start " << std::endl;
    

    return true;
}

