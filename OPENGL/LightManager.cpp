#include "LightManager.h"
void LightManager::UpdateShadowMaps ( const std::vector<Object*>& sceneObjects ) {

	glClear ( GL_DEPTH_BUFFER_BIT );
	glEnable ( GL_CULL_FACE );
	glCullFace ( GL_FRONT_FACE );


	for ( auto& light : lightMass ) {
		light->m_shadowMap->Bind ( );
		glViewport ( 0 , 0 ,
		light->m_shadowMap->GetShadowMap ( )->GetWidth ( ) ,
		light->m_shadowMap->GetShadowMap ( )->GetHeight ( ) );
		glClear ( GL_DEPTH_BUFFER_BIT );


		std::cout <<"AAA" << sizeof ( glm::vec3 ) << std::endl;
		// 모든 오브젝트를 쉐도우맵에 렌더링
		for ( auto* object : sceneObjects ) {
			if ( object->typeID == 0 ) {
				m_simpleProgram->Use ( );

				m_simpleProgram->SetUniform ( "color" , glm::vec4 ( 1.0f , 1.0f , 1.0f , 1.0f ) );
				object->RenderShadow ( light->lightProjection * light->lightView , m_simpleProgram );
			}
			else if ( object->typeID == 1 ) {
				m_simpleAnimationProgram->Use ( );

				m_simpleAnimationProgram->SetUniform ( "color" , glm::vec4 ( 1.0f , 1.0f , 1.0f , 1.0f ) );
				object->RenderShadow ( light->lightProjection * light->lightView , m_simpleAnimationProgram );
			}
		
		}

		Framebuffer::BindToDefault ( );
	}

	glDisable ( GL_CULL_FACE );


}


void LightManager::GetLightSetting ( const Program* programs ) {

	//UBOLight->Bind ( programs->Get ( ) , "Dlights" );
	//UBOLight->UpdateData ( m_lights );
	uint32_t program = programs->Get ( );

	std::cerr << m_lights[ 0 ].direction[ 0 ] << std::endl;
	std::cerr << m_lights[ 0 ].direction[ 1 ] << std::endl;
	std::cerr << m_lights[ 0 ].direction[ 2 ] << std::endl;
	std::cerr << "m_lights[ 0 ].position[ 0 ]" << std::endl;

	glUniform1i ( glGetUniformLocation ( program , "numLights" ) , LightNum );

	for ( int i = 0; i < LightNum; ++i ) {
		std::string base = "lights[" + std::to_string ( i ) + "].";

		glUniform1i ( glGetUniformLocation ( program , ( base + "directional" ).c_str ( ) ) , m_lights[ i ].directional );
		glUniform3fv ( glGetUniformLocation ( program , ( base + "position" ).c_str ( ) ) , 1 , glm::value_ptr ( m_lights[ i ].position ) );
		glUniform3fv ( glGetUniformLocation ( program , ( base + "direction" ).c_str ( ) ) , 1 , glm::value_ptr ( m_lights[ i ].direction ) );
		glUniform2fv ( glGetUniformLocation ( program , ( base + "cutoff" ).c_str ( ) ) , 1 , glm::value_ptr ( m_lights[ i ].cutoff ) );
		glUniform3fv ( glGetUniformLocation ( program , ( base + "attenuation" ).c_str ( ) ) , 1 , glm::value_ptr ( m_lights[ i ].attenuation ) );
		glUniform3fv ( glGetUniformLocation ( program , ( base + "ambient" ).c_str ( ) ) , 1 , glm::value_ptr ( m_lights[ i ].ambient ) );
		glUniform3fv ( glGetUniformLocation ( program , ( base + "diffuse" ).c_str ( ) ) , 1 , glm::value_ptr ( m_lights[ i ].diffuse ) );
		glUniform3fv ( glGetUniformLocation ( program , ( base + "specular" ).c_str ( ) ) , 1 , glm::value_ptr ( m_lights[ i ].specular ) );
	}

}

void LightManager::UpdateShadowMapping (const Program* program )
{

	program->SetUniform ( "numLights" , LightNum );
	for ( int i = 0; i < LightNum; i++ ) {
		std::string base = "lightTransform[" + std::to_string ( i ) + "]";

		auto lightTransform = LightManager::getInstance ( ).GetLightTransform ( i ); // 라이트의 lightSpaceMatrix 계산

		glUniformMatrix4fv ( glGetUniformLocation ( program->Get() , ( base ).c_str ( ) ) , 1 , GL_FALSE , glm::value_ptr ( lightTransform ) );


		glActiveTexture ( GL_TEXTURE0 + 5 + i );
		base = "shadowMaps[" + std::to_string ( i ) + "]";
		LightManager::getInstance ( ).GetShadowMap ( i )->GetShadowMap ( )->Bind ( );
		// m_lightingShadowProgram->SetUniform ( "shadowMap[" + std::to_string ( i ) + "]" , 3+i );  // 각 라이트의 그림자 맵 바인딩
		glUniform1i ( glGetUniformLocation ( program->Get ( ) , ( base ).c_str ( ) ) , 5 + i );

		std::cout << glGetUniformLocation ( program->Get ( ) , ( base ).c_str ( ) ) << std::endl;

	}

	glActiveTexture ( GL_TEXTURE0 );
}
