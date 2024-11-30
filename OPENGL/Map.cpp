#include "Map.h"
#include "Time.h"
#include "LightManager.h"
#include "RandomEngine.h"


void Map::Update ( )
{
    CameraLightUpdate ( );
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
	
    UBO = UBOBUFFER_LIGHT::Create ( 20 );
	ground = Mesh::CreatePlane ( );
	m_model = Model::Load ( strName );
	std::cerr << "MAPAA" << std::endl;
	
    if ( !m_model ) {
        std::cerr << "program UserSetError id : " << m_model->Get ( ) << std::endl;
        return;


    }
    SettingCamera ( );
    SettingLight ( );


	
}

void Map::SettingCamera ( )
{


    camera1 = new Camera;
    camera1->SetCamera ( glm::vec3 ( 33.f , 10.f , -54.f ) , glm::vec3 ( 33.f , 0.f , -54.f ) );
    camera.push_back ( camera1 );
    
    camera1 = new Camera;
    camera1->SetCamera ( glm::vec3 ( 45.0f , 10.0f , -26.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) );
    camera.push_back ( camera1 );
    
    for ( auto& _camera : camera ) {
        CameraManager::getInstance ( ).AddCamera ( _camera );
    }
    CameraManager::getInstance ( ).SetCamera2 ( camera[0] );
}

void Map::SettingLight ( ) {


    light1 = new LightMass;
    light1->SetLight ( glm::vec3 ( -36.0f , 1.5f , -5.5f ) , glm::vec3 ( 0.8f , 0.0f , -3.0f ) , glm::vec2 ( 4.0f , 24.0f ) , 150.0f );
    sitghtlight.push_back ( light1 );

    light1 = new LightMass;
    light1->SetLight ( glm::vec3 ( -38.0f , 1.5f , -5.0f ) , glm::vec3 ( -0.8f , 0.0f , -3.0f ) , glm::vec2 ( 4.0f , 24.0f ) , 150.0f );
    sitghtlight.push_back ( light1 );

    light1 = new LightMass;
    light1->SetLight ( glm::vec3 ( 66.0f , 15.0f , -60.0f ) , glm::vec3 ( 3.0f , 0.0f , 2.0f ) , glm::vec2 ( 23.0f , 16.0f ) ,
        150.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 165.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    sitghtlight.push_back ( light1 );

    light1 = new LightMass;
    light1->SetLight ( glm::vec3 ( 33.0f , 15.0f , -54.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 9.0f , 5.0f ) ,
        270.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 165.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    sitghtlight.push_back ( light1 );

    light1 = new LightMass;
    light1->SetLight ( glm::vec3 ( 45.0f , 12.0f , -26.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 14.5f , 18.0f ) ,
        270.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    sitghtlight.push_back ( light1 );

    light1 = new LightMass;
    light1->SetLight ( glm::vec3 ( 66.0f , 12.0f , -18.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 2.5f , 18.0f ) ,
        270.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    sitghtlight.push_back ( light1 );

    light1 = new LightMass;
    light1->SetLight ( glm::vec3 ( 84.0f , 7.0f , -8.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 10.0f , 18.0f ) ,
        270.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    sitghtlight.push_back ( light1 );

    light1 = new LightMass;
    light1->SetLight ( glm::vec3 ( 112.0f , 7.0f , -7.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 14.0f , 18.0f ) ,
        270.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    sitghtlight.push_back ( light1 );

    light1 = new LightMass;
    light1->SetLight ( glm::vec3 ( 110.0f , 9.0f , -40.0f ) , glm::vec3 ( 0.0f , -3.0f , -4.0f ) , glm::vec2 ( 15.0f , 28.0f ) ,
        232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    sitghtlight.push_back ( light1 );

    light1 = new LightMass;
    light1->SetLight ( glm::vec3 ( 94.0f , 7.5f , -60.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 3.0f , 28.0f ) ,
        232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) );
    sitghtlight.push_back ( light1 );

    light1 = new LightMass;
    light1->SetLight ( glm::vec3 ( 60.0f , 13.0f , -88.0f ) , glm::vec3 ( 1.15f , -3.0f , 0.0f ) , glm::vec2 ( 25.0f , 28.0f ) ,
        232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    sitghtlight.push_back ( light1 );

    light1 = new LightMass;
    light1->SetLight ( glm::vec3 ( 42.0f , 18.0f , -84.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 6.8f , 30.0f ) ,
        232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    sitghtlight.push_back ( light1 );

    light1 = new LightMass;
    light1->SetLight ( glm::vec3 ( 21.0f , 12.0f , -105.0f ) , glm::vec3 ( 0.0f , -3.0f , 0.0f ) , glm::vec2 ( 24.0f , 11.0f ) ,
        232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    sitghtlight.push_back ( light1 );

    light1 = new LightMass;
    light1->SetLight ( glm::vec3 ( 64.0f , 13.0f , -115.0f ) , glm::vec3 ( 1.0f , -3.0f , 0.0f ) , glm::vec2 ( 24.0f , 11.0f ) ,
        232.0f , glm::vec3 ( 0.0f , 0.0f , 0.0f ) , glm::vec3 ( 150.0f , 0.0f , 0.0f ) , glm::vec3 ( 250.0f , 0.0f , 0.0f ) );
    sitghtlight.push_back ( light1 );

    for ( auto& _light : sitghtlight ) {
        LightManager::getInstance ( ).AddLight ( _light );
    }
    sitghtlight[ 3 ]->Switch_lightControl ( ) = true;
}

void Map::CameraLightUpdate ( )
{
   

    updateSightTime += Time::DeltaTime ( );
    int newCameraID = usingCameraID;
    std::cerr << updateSightTime << std::endl;
    if ( updateSightTime >= 12.0f ) {
     
        std::uniform_int_distribution<int> camera_moving ( 0 , 0 );

        newCameraID = camera_moving ( RandomEngine::GetEngine() );
        std::cerr << newCameraID << std::endl;
        std::cerr << "이종현 씨붕방넘아" << std::endl;
        updateSightTime = 0.0f;
    }
    


    
    
    if ( usingCameraID != newCameraID ) {
        sitghtlight[ usingCameraID ]->Switch_lightControl ( ) = false;
        usingCameraID = newCameraID;
        sitghtlight[ usingCameraID ]->Switch_lightControl() = true;
        CameraManager::getInstance ( ).SetCamera2 ( camera[usingCameraID] );
    }
   
}

void Map::CollisionLight ( )
{

}

void Map::RenderShadow ( glm::mat4 lightView , const Program* program )
{
    program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos )  );
    program->SetUniform ( "transform" , lightView * glm::translate ( glm::mat4 ( 1.0f ) , Pos ));
    //std::cout << "model" << std::endl;
    m_model->Draw ( program );
}

