#include "Map.h"
#include "Time.h"
#include "LightManager.h"

void Map::Update ( )
{
}

void Map::Render ( const Program* program )
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

	
}

void Map::RenderShadow ( glm::mat4 lightView , const Program* program )
{
    program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos )  );
    program->SetUniform ( "transform" , lightView * glm::translate ( glm::mat4 ( 1.0f ) , Pos ));
    //std::cout << "model" << std::endl;
    m_model->Draw ( program );
}
