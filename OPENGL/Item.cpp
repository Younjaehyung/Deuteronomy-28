#include "Item.h"
#include "Time.h"
#include "LightManager.h"
#include "CollisionManager.h"

void Item::Update ( ) {
        
    itemRotatef += Time::DeltaTime() * 50.0f; // 초당 50도 회전

    // 원점에서 회전
        itemRotate = glm::rotate(glm::mat4(1.0f), glm::radians( itemRotatef ), glm::vec3(0.0f, 1.0f, 0.0f));



   
}

void Item::Render ( const Program* program , glm::mat4 _cameraTransform ) {
    if ( model ) {
        program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * itemRotate );
        program->SetUniform ( "transform" , _cameraTransform *
                                          glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * itemRotate );
        LightManager::getInstance ( ).GetLightSetting ( program );
        model->Draw ( program );
    }
}

void Item::Render_2pass ( const Program* program, glm::mat4 _cameraTransform ) {
    if ( model ) {
        program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos )* itemRotate );
        program->SetUniform ( "transform" , _cameraTransform *
                                          glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * itemRotate );
        LightManager::getInstance ( ).GetLightSetting ( program );
        model->Draw ( program );
    }
}

void Item::RenderShadow ( glm::mat4 lightView , const Program* program ) {
    if ( model ) {
        program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * itemRotate );
        program->SetUniform ( "transform" , lightView * glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * itemRotate );
        model->Draw ( program );
    }
}

bool Item::HandleCollision ( Object* player )
{

    if ( player->objectID == eLayerType::Player ) {
        SoundManager::getInstance ( ).GetSoundID ( "GetItem" )->ReplaySound ( );
        GetDestroy ( ) = 1;
        
    }
    
    return true;
}







void Item::Initialize ( const std::string& strName ) {
    model = Model::Load ( strName );
    if ( !model ) {
        std::cerr << "Failed to load model for Item: " << strName << std::endl;
        throw std::runtime_error ( "Item initialization failed" );
    }
    std::cerr << "Item initialized: " << strName << std::endl;
}