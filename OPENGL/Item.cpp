#include "Item.h"
#include "Time.h"
#include "LightManager.h"

void Item::Update ( ) {
    // 아이템은 정적이므로 업데이트 필요 없음
}

void Item::Render_2pass ( const Program* program ) {
    if ( model ) {
        program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) );
        program->SetUniform ( "transform" , CameraManager::getInstance ( ).Camera_transform ( ) *
                                          glm::translate ( glm::mat4 ( 1.0f ) , Pos ) );
        LightManager::getInstance ( ).GetLightSetting ( program );
        model->Draw ( program );
    }
}

void Item::RenderShadow ( glm::mat4 lightView , const Program* program ) {
    if ( model ) {
        program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) );
        program->SetUniform ( "transform" , lightView * glm::translate ( glm::mat4 ( 1.0f ) , Pos ) );
        model->Draw ( program );
    }
}

void Item::HandleCollision ( Object* player )
{
    if ( player->objectID == eLayerType::Player ) {


    }


}



void Item::Render ( const Program* program ) {
    if ( model ) {
        program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) );
        program->SetUniform ( "transform" , CameraManager::getInstance ( ).Camera_transform ( ) *
                                          glm::translate ( glm::mat4 ( 1.0f ) , Pos ) );
        model->Draw ( program );
    }
}



void Item::Initialize ( const std::string& strName ) {
    model = Model::Load ( strName );
    if ( !model ) {
        std::cerr << "Failed to load model for Item: " << strName << std::endl;
        throw std::runtime_error ( "Item initialization failed" );
    }
    std::cerr << "Item initialized: " << strName << std::endl;
}