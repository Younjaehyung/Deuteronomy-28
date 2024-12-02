#include "Map.h"
#include "Time.h"
#include "LightManager.h"
#include "RandomEngine.h"
#include "character.h"

void Map::Update ( )
{
    CameraLightUpdate ( );
    CollisionLight ( );
}

void Map::Render ( const Program* program, glm::mat4 _cameraTransform )
{


    //for ( size_t i = 0; i < lights.size ( ); ++i ) {
    //    std::string index = std::to_string ( i );

    //    glUniform3fv ( glGetUniformLocation ( program , ( "lights[" + index + "].position" ).c_str ( ) ) , 1 , &lights[ i ].position[ 0 ] );
    //    glUniform3fv ( glGetUniformLocation ( program , ( "lights[" + index + "].direction" ).c_str ( ) ) , 1 , &lights[ i ].direction[ 0 ] );
    //    glUniform3fv ( glGetUniformLocation ( program , ( "lights[" + index + "].ambient" ).c_str ( ) ) , 1 , &lights[ i ].ambient[ 0 ] );
    //    glUniform3fv ( glGetUniformLocation ( program , ( "lights[" + index + "].diffuse" ).c_str ( ) ) , 1 , &lights[ i ].diffuse[ 0 ] );
    //    glUniform3fv ( glGetUniformLocation ( program , ( "lights[" + index + "].specular" ).c_str ( ) ) , 1 , &lights[ i ].specular[ 0 ] );

    //    // 조명 타입에 따른 추가 설정
    //    if ( lights[ i ].type == POINT_LIGHT || lights[ i ].type == SPOT_LIGHT ) {
    //        glUniform3fv ( glGetUniformLocation ( program , ( "lights[" + index + "].attenuation" ).c_str ( ) ) , 1 , &lights[ i ].attenuation[ 0 ] );
    //    }
    //    if ( lights[ i ].type == SPOT_LIGHT ) {
    //        glUniform2fv ( glGetUniformLocation ( program , ( "lights[" + index + "].cutoff" ).c_str ( ) ) , 1 , &lights[ i ].cutoff[ 0 ] );
    //    }
    //}

    /*program->SetUniform ( "modelTransform" , CameraManager::getInstance ( ).Camera_transform ( ) );
    program->SetUniform ( "model" ,glm::rotate( glm::mat4 ( 1.0f ) ,glm::radians(90.0f),glm::vec3(0.0f,1.0f,0.0f  ))* glm::translate ( glm::mat4 ( 1.0f ) , glm::vec3 ( 0.0f , 0.0f , +30.0f )) );
    program->SetUniform ( "viewPos" , CameraManager::getInstance().GetCameraPos() );
    program->SetUniform ( "numLights" , 4);
    program->SetUniform ( "color" , glm::vec3 ( 0.3f ) );
    UBO->Bind ( program->Get ( ) , "lights" );
    UBO->UpdateData ( _model->GetLight() );*/
    LightManager::getInstance ( ).GetLightSetting ( program );
		m_model->Draw ( program );

        
		//program->SetUniform ( "transform" , CameraManager::getInstance().Camera_transform()*glm::rotate( glm::mat4 ( 1.0f ),glm::radians(90.0f ),glm::vec3(1.0f,0.0f,0.0f) )
			//*glm::scale ( glm::mat4 ( 1.0f ) ,glm::vec3(100.0f,100.0f,100.0f) ) );
		//ground->Draw ( program );
}


void Map::Initialize ( const std::string& strName )
{
	
    //UBO = UBOBUFFER_LIGHT::Create ( 30 );
	ground = Mesh::CreatePlane ( );
	m_model = Model::Load ( strName );

    if ( !m_model ) {
        std::cerr << "program UserSetError id : " << m_model->Get ( ) << std::endl;
        return;


    }
    SettingCamera ( );
    SettingLight ( );


	
}

void Map::SettingCamera ( )
{

    SightLight* newInstance = new SightLight;
    Camera* camera1 = new Camera;   //홀
    camera1->SetCamera ( glm::vec3 ( 78.0f , 12.0f , -54.0f ) , glm::vec3 ( 59.0f , 0.0f , -54.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    newInstance->mapCamera = camera1;
    LightMass* Light1 = new LightMass;
    Light1->SetLight ( glm::vec3 ( 39.0f , 15.0f , -54.0f ) , glm::vec3 ( -1.0f , -3.0f , 0.0f ) , glm::vec2 ( 15.0f , 10.0f ) ,
        232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    newInstance->Visullight.push_back ( Light1 );

    LightMass* Corridor1 = new LightMass;
    Corridor1->SetPos ( glm::vec3 ( 38.0f , 0.0f , -50.0f ) );
    Corridor1->SetBox ( glm::vec3 ( 6.0f ) , "Hall" );
    newInstance->CollisionLight.push_back ( Corridor1 );
    Corridor1->SetobjectID ( eLayerType::Light );
    sightLight.push_back ( newInstance );

    newInstance = new SightLight;
    camera1 = new Camera;   //방1번 출구
    camera1->SetCamera ( glm::vec3 ( 69.0f , 5.3f , -13.0f ) , glm::vec3 ( 54.0f , 0.0f , -23.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    newInstance->mapCamera = camera1;
    Light1 = new LightMass;
    Light1->SetLight ( glm::vec3 ( 66.0f , 12.0f , -18.0f ) , glm::vec3 ( -1.5f , -3.0f , 0.0f ) , glm::vec2 ( 15.0f , 30.0f ) ,
        232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    newInstance->Visullight.push_back ( Light1 );
    Corridor1 = new LightMass;
    Corridor1->SetPos ( glm::vec3 ( 62.0f , 0.0f , -20.0f ) );
    Corridor1->SetBox ( glm::vec3 ( 8.0f ) , "Room" );
    newInstance->CollisionLight.push_back ( Corridor1 );
    Corridor1->SetobjectID ( eLayerType::Light );
    sightLight.push_back ( newInstance );

    newInstance = new SightLight;
    camera1 = new Camera;   //방1 -> 방2 복도
    camera1->SetCamera ( glm::vec3 ( 116.0f , 6.0f , -4.0f ) , glm::vec3 ( 100.0f , 0.0f , -8.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    newInstance->mapCamera = camera1;
    //Light1 = new LightMass;
    //Light1->SetLight ( glm::vec3 ( 90.0f , 7.0f , -8.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 30.0f , 15.0f ) ,
    //    232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    //newInstance->Visullight.push_back ( Light1 );
    LightMass* Light2 = new LightMass;
    Light2->SetLight ( glm::vec3 ( 116.0f , 4.5f , -6.0f ) , glm::vec3 ( -4.0f , -3.0f , 1.5f ) , glm::vec2 ( 50.0f , 15.0f ) ,
        232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    newInstance->Visullight.push_back ( Light2 );
    Light2 = new LightMass;
    Corridor1 = new LightMass;
    Corridor1->SetPos ( glm::vec3 ( 111.0f , 0.0f , -8.0f ) );
    Corridor1->SetBox ( glm::vec3 ( 5.0f ) , "Room" );
    newInstance->CollisionLight.push_back ( Corridor1 );
    Corridor1->SetobjectID ( eLayerType::Light );
    sightLight.push_back ( newInstance );

    newInstance = new SightLight;
    camera1 = new Camera;   //마네킹 방
    camera1->SetCamera ( glm::vec3 ( 120.0f , 6.0f , -55.0f ) , glm::vec3 ( 120.0f , 0.0f , -24.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    newInstance->mapCamera = camera1;
    Light1 = new LightMass;
    Light1->SetLight ( glm::vec3 ( 110.0f , 9.0f , -40.0f ) , glm::vec3 ( 0.0f , -3.0f , -4.0f ) , glm::vec2 ( 1.5f , 28.0f ) ,
        232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) );
    newInstance->Visullight.push_back ( Light1 );
    Light2 = new LightMass;
    Light2->SetLight ( glm::vec3 ( 102.0f , 6.0f , -55.0f ) , glm::vec3 ( 3.0f , -3.0f , 3.0f ) , glm::vec2 ( 30.0f , 15.0f ) ,
        232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    newInstance->Visullight.push_back ( Light2 );
    Corridor1 = new LightMass;
    Corridor1->SetPos ( glm::vec3 ( 108.0f , 0.0f , -38.0f ) );
    Corridor1->SetBox ( glm::vec3 ( 8.0f ) , "Manequin" );
    newInstance->CollisionLight.push_back ( Corridor1 );
    Corridor1->SetobjectID ( eLayerType::Light );
    sightLight.push_back ( newInstance );

    newInstance = new SightLight;
    camera1 = new Camera;   //마네킹방 -> 복도
    camera1->SetCamera ( glm::vec3 ( 92.0f , 6.0f , -25.0f ) , glm::vec3 ( 94.0f , 0.0f , -36.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    newInstance->mapCamera = camera1;
    Light1 = new LightMass;
    Light1->SetLight ( glm::vec3 ( 94.0f , 8.0f , -21.0f ) , glm::vec3 ( 0.0f , -3.0f , -3.0f ) , glm::vec2 ( 20.0f , 10.0f ) ,
        232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    newInstance->Visullight.push_back ( Light1 );
    Corridor1 = new LightMass;
    Corridor1->SetPos ( glm::vec3 ( 95.0f , 0.0f , -26.0f ) );
    Corridor1->SetBox ( glm::vec3 ( 5.0f ) , "bokdo2" );
    newInstance->CollisionLight.push_back ( Corridor1 );
    Corridor1->SetobjectID ( eLayerType::Light );
    newInstance->CollisionLight.push_back ( Corridor1 );
    sightLight.push_back ( newInstance );

    newInstance = new SightLight;
    camera1 = new Camera;   //엉덩이탐정 복도 끝
    camera1->SetCamera ( glm::vec3 ( 98.0f , 6.0f , -100.0f ) , glm::vec3 ( 94.0f , 0.0f , -85.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    newInstance->mapCamera = camera1;
    Light1 = new LightMass;
    Light1->SetLight ( glm::vec3 ( 94.0f , 7.5f , -88.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 3.0f , 28.0f ) ,
        232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    newInstance->Visullight.push_back ( Light1 );
    Light2 = new LightMass;
    Light2->SetLight ( glm::vec3 ( 98.0f , 6.0f , -106.0f ) , glm::vec3 ( -1.5f , -3.0f , 1.1f ) , glm::vec2 ( 20.0f , 20.0f ) ,
        232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    newInstance->Visullight.push_back ( Light2 );
    Corridor1 = new LightMass;
    Corridor1->SetPos ( glm::vec3 ( 95.0f , 0.0f , -95.0f ) );
    Corridor1->SetBox ( glm::vec3 ( 5.0f ) , "bokdo3" );
    newInstance->CollisionLight.push_back ( Corridor1 );
    Corridor1->SetobjectID ( eLayerType::Light );
    sightLight.push_back ( newInstance );

    newInstance = new SightLight;
    camera1 = new Camera;   //살덩이 방
    camera1->SetCamera ( glm::vec3 ( 55.0f , 3.5f , -85.0f ) , glm::vec3 ( 66.0f , 0.0f , -88.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    newInstance->mapCamera = camera1;
    Light1 = new LightMass;
    Light1->SetLight ( glm::vec3 ( 60.0f , 13.0f , -88.0f ) , glm::vec3 ( -1.15f , -3.0f , 0.0f ) , glm::vec2 ( 25.0f , 28.0f ) ,
        232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    newInstance->Visullight.push_back ( Light1 );
    Corridor1 = new LightMass;
    Corridor1->SetPos ( glm::vec3 ( 61.0f , 0.0f , -89.0f ) );
    Corridor1->SetBox ( glm::vec3 ( 5.0f ) , "fleshroom1" );
    newInstance->CollisionLight.push_back ( Corridor1 );
    Corridor1->SetobjectID ( eLayerType::Light );
    sightLight.push_back ( newInstance );

    newInstance = new SightLight;
    camera1 = new Camera;   //살덩이 방2
    camera1->SetCamera ( glm::vec3 ( 42.0f , 6.0f , -78.0f ) , glm::vec3 ( 30.0f , 0.0f , -36.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    newInstance->mapCamera = camera1;
    Light1 = new LightMass;
    Light1->SetLight ( glm::vec3 ( 42.0f , 6.0f , -78.0f ) , glm::vec3 ( -3.0f , -3.0f , -1.5f ) , glm::vec2 ( 25.0f , 20.0f ) ,
        232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    newInstance->Visullight.push_back ( Light1 );
    Corridor1 = new LightMass;
    Corridor1->SetPos ( glm::vec3 ( 37.0f , 0.0f , -83.0f ) );
    Corridor1->SetBox ( glm::vec3 ( 5.0f ) , "fleshroom2" );
    newInstance->CollisionLight.push_back ( Corridor1 );
    Corridor1->SetobjectID ( eLayerType::Light );
    sightLight.push_back ( newInstance );

    newInstance = new SightLight;
    camera1 = new Camera;   //살덩이 방3
    camera1->SetCamera ( glm::vec3 ( 65.0f , 9.0f , -114.0f ) , glm::vec3 ( 50.0f , 0.0f , -115.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    newInstance->mapCamera = camera1;
    Light1 = new LightMass;
    Light1->SetLight ( glm::vec3 ( 65.0f , 9.0f , -114.0f ) , glm::vec3 ( 1.0f , -3.0f , 0.0f ) , glm::vec2 ( 30.0f , 20.0f ) ,
        232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    newInstance->Visullight.push_back ( Light1 );
    Corridor1 = new LightMass;
    Corridor1->SetPos ( glm::vec3 ( 60.0f , 0.0f , -110.0f ) );
    Corridor1->SetBox ( glm::vec3 ( 10.0f ) , "fleshroom3" );
    newInstance->CollisionLight.push_back ( Corridor1 );
    Corridor1->SetobjectID ( eLayerType::Light );
    sightLight.push_back ( newInstance );

    LightMass* Light5 = new LightMass; //홀
    Light5->SetLight ( glm::vec3 ( 66.0f , 15.0f , -60.0f ) , glm::vec3 ( 3.0f , 0.0f , 2.0f ) , glm::vec2 ( 23.0f , 116.0f ) ,
        150.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 165.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    normalLight.push_back ( Light5 );

    LightMass* Light3 = new LightMass;//자동차 헤드라이트 1
    Light3->SetLight ( glm::vec3 ( -36.0f , 0.5f , -7.5f ) , glm::vec3 ( 0.8f , 0.2f , -3.0f ) , glm::vec2 ( 8.0f , 24.0f ) ,
        250.0f , glm::vec3 ( 10.0f , 10.0f , 10.0f ) , glm::vec3 ( 255.0f , 255.0f , 255.0f ) , glm::vec3 ( 255.0f , 255.0f , 255.0f ) );

    normalLight.push_back ( Light3 );

    LightMass* Light4 = new LightMass;//자동차 헤드라이트
    Light4->SetLight ( glm::vec3 ( -38.0f , 0.5f , -7.0f ) , glm::vec3 ( -0.8f , 0.2f , -3.0f ) , glm::vec2 ( 8.0f , 24.0f ) ,
        250.0f , glm::vec3 ( 10.0f , 10.0f , 10.0f ) , glm::vec3 ( 255.0f , 255.0f , 255.0f ) , glm::vec3 ( 255.0f , 255.0f , 255.0f ) );
    normalLight.push_back ( Light4 );


    //camera1 = new Camera;   //홀
    //camera1->SetCamera ( glm::vec3 ( 78.0f , 12.0f , -54.0f ) , glm::vec3 ( 59.0f , 0.0f , -54.0f ), glm::vec3(0.0f, 1.0f, 0.0f) );
    //camera.push_back ( camera1 );
    //
    //camera1 = new Camera;//방1번 출구
    //camera1->SetCamera ( glm::vec3 ( 69.0f , 5.3f , -13.0f ) , glm::vec3 ( 54.0f , 0.0f , -23.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    //camera.push_back ( camera1 );

    //camera1 = new Camera;//방1->방2 복도
    //camera1->SetCamera ( glm::vec3 ( 116.0f , 6.0f , -4.0f ) , glm::vec3 ( 100.0f , 0.0f , -8.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    //camera.push_back ( camera1 );

    //camera1 = new Camera;//마네킹 방
    //camera1->SetCamera ( glm::vec3 ( 120.0f , 6.0f , -55.0f ) , glm::vec3 ( 120.0f , 0.0f , -24.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    //camera.push_back ( camera1 );

    //camera1 = new Camera;//마네킹 방 -> 복도
    //camera1->SetCamera ( glm::vec3 ( 92.0f , 6.0f , -25.0f ) , glm::vec3 ( 94.0f , 0.0f , -36.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    //camera.push_back ( camera1 );

    //camera1 = new Camera;//엉덩이탐정 복도 끝쪽
    //camera1->SetCamera ( glm::vec3 ( 98.0f , 6.0f , -100.0f ) , glm::vec3 ( 94.0f , 0.0f , -85.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    //camera.push_back ( camera1 );

    //camera1 = new Camera;//살덩이방 입구
    //camera1->SetCamera ( glm::vec3 ( 55.0f , 3.5f , -85.0f ) , glm::vec3 ( 66.0f , 0.0f , -88.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    //camera.push_back ( camera1 );

    //camera1 = new Camera;//살덩이방 -> 메인홀
    //camera1->SetCamera ( glm::vec3 ( 42.0f , 6.0f , -78.0f ) , glm::vec3 ( 30.0f , 0.0f , -36.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    //camera.push_back ( camera1 );

    //camera1 = new Camera;//살덩이방 끝
    //camera1->SetCamera ( glm::vec3 ( 65.0f , 9.0f , -114.0f ) , glm::vec3 ( 50.0f , 0.0f , -115.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    //camera.push_back ( camera1 );
    
    for ( auto& object : sightLight ) {
        //for (auto& light : object->CollisionLight ) {

        //}
        for ( auto& light : object->Visullight ) {
            
            LightManager::getInstance ( ).AddLight ( light );
        }
        
        CameraManager::getInstance ( ).SetCamera2 ( object->mapCamera );
        //CameraManager::getInstance ( ).AddCamera ( _camera );
    }
    
    for ( auto& light : normalLight ) {

        LightManager::getInstance ( ).AddLight ( light );
    }


}

void Map::SettingLight ( ) {


    //light1 = new SightLight;//0
    //light1->sightlight->SetLight ( glm::vec3 ( -36.0f , 1.5f , -5.5f ) , glm::vec3 ( 0.8f , 0.0f , -3.0f ) , glm::vec2 ( 4.0f , 24.0f ) , 150.0f );
    //sighttLight.push_back ( light1 );

    //light1 = new SightLight;//1
    //light1->sightlight->SetLight ( glm::vec3 ( -38.0f , 1.5f , -5.0f ) , glm::vec3 ( -0.8f , 0.0f , -3.0f ) , glm::vec2 ( 4.0f , 24.0f ) , 150.0f );
    //sighttLight.push_back ( light1 );

    //light1 = new SightLight;//2
    //light1->sightlight->SetLight ( glm::vec3 ( 66.0f , 15.0f , -60.0f ) , glm::vec3 ( 3.0f , 0.0f , 2.0f ) , glm::vec2 ( 23.0f , 116.0f ) ,
    //    150.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 165.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    //sighttLight.push_back ( light1 );

    //light1 = new SightLight;//3
    //light1->sightlight->SetLight ( glm::vec3 ( 33.0f , 15.0f , -54.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 9.0f , 5.0f ) ,
    //    270.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 165.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    //sighttLight.push_back ( light1 );

    //light1 = new SightLight;//4
    //light1->sightlight->SetLight ( glm::vec3 ( 45.0f , 12.0f , -26.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 14.5f , 18.0f ) ,
    //    270.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    //sighttLight.push_back ( light1 );

    //light1 = new SightLight;//5
    //light1->sightlight->SetLight ( glm::vec3 ( 66.0f , 12.0f , -18.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 2.5f , 18.0f ) ,
    //    270.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    //sighttLight.push_back ( light1 );

    //light1 = new SightLight;//6
    //light1->sightlight->SetLight ( glm::vec3 ( 84.0f , 7.0f , -8.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 10.0f , 18.0f ) ,
    //    270.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    //sighttLight.push_back ( light1 );

    //light1 = new SightLight;//7
    //light1->sightlight->SetLight ( glm::vec3 ( 112.0f , 7.0f , -7.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 14.0f , 18.0f ) ,
    //    270.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    //sighttLight.push_back ( light1 );

    //light1 = new SightLight;//8
    //light1->sightlight->SetLight ( glm::vec3 ( 110.0f , 9.0f , -40.0f ) , glm::vec3 ( 0.0f , -3.0f , -4.0f ) , glm::vec2 ( 15.0f , 28.0f ) ,
    //    232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    //sighttLight.push_back ( light1 );

    //light1 = new SightLight;//9
    //light1->sightlight->SetLight ( glm::vec3 ( 94.0f , 7.5f , -60.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 3.0f , 28.0f ) ,
    //    232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) );
    //sighttLight.push_back ( light1 );

    //light1 = new SightLight;//10
    //light1->sightlight->SetLight ( glm::vec3 ( 60.0f , 13.0f , -88.0f ) , glm::vec3 ( 1.15f , -3.0f , 0.0f ) , glm::vec2 ( 25.0f , 28.0f ) ,
    //    232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    //sighttLight.push_back ( light1 );

    //light1 = new SightLight;//11
    //light1->sightlight->SetLight ( glm::vec3 ( 42.0f , 18.0f , -84.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 6.8f , 30.0f ) ,
    //    232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    //sighttLight.push_back ( light1 );

    //light1 = new SightLight;//12
    //light1->sightlight->SetLight ( glm::vec3 ( 21.0f , 12.0f , -105.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 24.0f , 11.0f ) ,
    //    232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    //sighttLight.push_back ( light1 );

    //light1 = new SightLight;//13
    //
    //LightMass* ex = new LightMass;
    //light1->sightlight->SetBox ( glm::vec3 ( ) , name );
    //ex->SetobjectID ( eLayerType::Light );

    //light1->sightlight->SetLight ( glm::vec3 ( 64.0f , 13.0f , -115.0f ) , glm::vec3 ( 1.0f , -3.0f , 0.0f ) , glm::vec2 ( 24.0f , 11.0f ) ,
    //    232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    //sighttLight.push_back ( light1 );

    //for ( auto& _light : sighttLight ) {
    //    LightManager::getInstance ( ).AddLight ( _light->sightlight );
    //}
    //sighttLight[ 3 ]->sightlight->Switch_lightControl ( ) = true;
}

void Map::CameraLightUpdate ( )
{
   

    updateSightTime += Time::DeltaTime ( );
    int newCameraID = usingCameraID;
    std::cerr <<"Camera TIme:" << updateSightTime << std::endl;
    if ( updateSightTime >= 12.0f ) {
     
        std::uniform_int_distribution<int> camera_moving ( 0 , 0 );

        newCameraID = camera_moving ( RandomEngine::GetEngine() );
        std::cerr << "Camera Update:" << newCameraID << std::endl;
        updateSightTime = 0.0f;
    }
    


    
    
    /*if ( usingCameraID != newCameraID ) {
        sighttLight[ usingCameraID ]->sightlight->Switch_lightControl ( ) = false;
        sighttLight[ usingCameraID ]->sightlight->GetCollisionLight ( ) = 0;
        usingCameraID = newCameraID;
        sighttLight[ usingCameraID ]->sightlight->GetCollisionLight ( ) = 0;
        sighttLight[ usingCameraID ]->sightlight->Switch_lightControl() = true;
        CameraManager::getInstance ( ).SetCamera2 ( camera[usingCameraID] );
    }*/
   
}

void Map::CollisionLight ( )
{
    for ( auto& _light : sightLight ) {
        for ( auto& collider : _light->CollisionLight ) {
            if ( collider->GetCollisionLight ( ) ) {
                monster->notifyFromMap ( collider->GetPos() );
                collider->GetCollisionLight ( ) = 0;
                std::cout << "CollisionLight CollisionLight" << std::endl;
            }
           
        }
    }
   
    
}

void Map::RenderShadow ( glm::mat4 lightView , const Program* program )
{
    program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos )  );
    program->SetUniform ( "transform" , lightView * glm::translate ( glm::mat4 ( 1.0f ) , Pos ));
    //std::cout << "model" << std::endl;
    m_model->Draw ( program );
}

