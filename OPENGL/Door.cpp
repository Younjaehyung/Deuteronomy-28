#include "Door.h"
#include "Time.h"
#include "LightManager.h"
#include "CollisionManager.h"

void Door::Update ( ) {

        
        
    if ( ItemCount == 1 ) {
        if ( DoorRotatef==0.0f ) {
            SoundManager::getInstance ( ).GetSoundID ( "DoorOpen" )->ReplaySound (0.7f);
        }
        if ( DoorRotatef >= -120.0f ) {
            DoorRotatef += Time::DeltaTime ( ) * -15.0f; // 초당 50도 회전
            // 원점에서 회전
            DoorRotate = glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( DoorRotatef ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );

        }

    }
    else if ( ItemCount == 2 ) {
        if ( status == 0 ) {
            SoundManager::getInstance ( ).GetSoundID ( "DoorSlam" )->ReplaySound (0.5f);
            status = 1;
        }
        if ( DoorRotatef <= 0.0f ) {
            DoorRotatef += Time::DeltaTime ( ) * 60.0f; // 초당 50도 회전
            // 원점에서 회전
            DoorRotate = glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( DoorRotatef ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );

        }

    }
    else if ( ItemCount == 5 ) {
        if ( status == 1 ) {
            SoundManager::getInstance ( ).GetSoundID ( "DoorOpen" )->ReplaySound (0.7f);
            status = 2;
        }
        if ( DoorRotatef >= 120.0f ) {
            DoorRotatef += Time::DeltaTime ( ) * 15.0f; // 초당 50도 회전
            // 원점에서 회전
            DoorRotate = glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( DoorRotatef ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
           
        }
       
    }

}

void Door::GetItemCount (int ItemNumber) {
    ItemCount = ItemNumber;
}


void Door::Render ( const Program* program , glm::mat4 _cameraTransform ) {
    if ( model ) {
        program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * DoorRotate );
        program->SetUniform ( "transform" , _cameraTransform *
                                          glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * DoorRotate );
        LightManager::getInstance ( ).GetLightSetting ( program );
        model->Draw ( program );
    }
}

void Door::Render_2pass ( const Program* program , glm::mat4 _cameraTransform ) {
    if ( model ) {
        program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * DoorRotate );
        program->SetUniform ( "transform" , _cameraTransform *
                                          glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * DoorRotate );
        LightManager::getInstance ( ).GetLightSetting ( program );
        model->Draw ( program );
    }
}

void Door::RenderShadow ( glm::mat4 lightView , const Program* program ) {
    if ( model ) {
        program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * DoorRotate );
        program->SetUniform ( "transform" , lightView * glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * DoorRotate );
        model->Draw ( program );
    }
}

bool Door::HandleCollision ( Object* player )
{
    //std::cout << "나는 삭제왕 오승원이다3" << std::endl;
    //if ( player->objectID == eLayerType::Player ) {
    //    SoundManager::getInstance ( ).GetSoundID ( "GetItem" )->ReplaySound ( );
    //    GetDestroy ( ) = 1;

    //}

    return true;
}







void Door::Initialize ( const std::string& strName ) {
    model = Model::Load ( strName );
    if ( !model ) {
     //   std::cerr << "Failed to load model for Door: " << strName << std::endl;
        throw std::runtime_error ( "Door initialization failed" );
    }
  //  std::cerr << "Door initialized: " << strName << std::endl;
}