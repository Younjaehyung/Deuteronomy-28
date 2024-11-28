#include "LightManager.h"
#include "CameraManager.h"
#include "Player.h"
void LightManager::UpdateShadowMaps ( const std::vector<Object*>& sceneObjects ) {
	ableLightNum = 0;	//활성 빛 개수 초기화
	glClear ( GL_DEPTH_BUFFER_BIT );
	glEnable ( GL_CULL_FACE );
	glCullFace ( GL_FRONT_FACE );


	for ( auto& light : lightMass ) {
		if ( !light->Switch_lightControl ( ) ) {
			continue;
		}
		ableLightNum++;

		light->GetlightShadowMap ()->Bind ( );
		glViewport ( 0 , 0 ,
		light->GetlightShadowMap ()->GetShadowMap ( )->GetWidth ( ) ,
		light->GetlightShadowMap ()->GetShadowMap ( )->GetHeight ( ) );
		glClear ( GL_DEPTH_BUFFER_BIT );
		

		// 모든 오브젝트를 쉐도우맵에 렌더링
		for ( auto* object : sceneObjects ) {
			if ( object->typeID == 0 ) {
				m_simpleProgram->Use ( );

				m_simpleProgram->SetUniform ( "color" , glm::vec4 ( 1.0f , 1.0f , 1.0f , 1.0f ) );
				object->RenderShadow ( light->GetlightProjection() * light->GetlightView() , m_simpleProgram );
			}
			else if ( object->typeID == 1 ) {
				m_simpleAnimationProgram->Use ( );

				m_simpleAnimationProgram->SetUniform ( "color" , glm::vec4 ( 1.0f , 1.0f , 1.0f , 1.0f ) );
				object->RenderShadow ( light->GetlightProjection() * light->GetlightView() , m_simpleAnimationProgram );
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

	glUniform1i ( glGetUniformLocation ( program , "numLights" ) , ableLightNum );
	int index = 0;
	for ( int i = 0; i < ableLightNum; ++i ) {
		
		while ( !lightMass[ index ]->Switch_lightControl ( ) ) {
			index += 1;
		}

		std::string base = "lights[" + std::to_string ( i ) + "].";

		glUniform1i ( glGetUniformLocation ( program , ( base + "directional" ).c_str ( ) ) , lightMass[ index ]->GetlightData ( ).directional );
		glUniform3fv ( glGetUniformLocation ( program , ( base + "position" ).c_str ( ) ) , 1 , glm::value_ptr ( lightMass[ index ]->GetlightData ( ).position ) );
		glUniform3fv ( glGetUniformLocation ( program , ( base + "direction" ).c_str ( ) ) , 1 , glm::value_ptr ( lightMass[ index ]->GetlightData ( ).direction ) );
		glUniform2fv ( glGetUniformLocation ( program , ( base + "cutoff" ).c_str ( ) ) , 1 , glm::value_ptr ( lightMass[ index ]->GetlightData ( ).cutoff ) );
		glUniform3fv ( glGetUniformLocation ( program , ( base + "attenuation" ).c_str ( ) ) , 1 , glm::value_ptr ( lightMass[ index ]->GetlightData ( ).attenuation ) );
		glUniform3fv ( glGetUniformLocation ( program , ( base + "ambient" ).c_str ( ) ) , 1 , glm::value_ptr ( lightMass[ index ]->GetlightData ( ).ambient ) );
		glUniform3fv ( glGetUniformLocation ( program , ( base + "diffuse" ).c_str ( ) ) , 1 , glm::value_ptr ( lightMass[ index ]->GetlightData ( ).diffuse ) );
		glUniform3fv ( glGetUniformLocation ( program , ( base + "specular" ).c_str ( ) ) , 1 , glm::value_ptr ( lightMass[ index ]->GetlightData ( ).specular ) );
	
		index += 1;
	}

}

void LightManager::UpdateShadowMapping (const Program* program )
{
	int index = 0;
	program->SetUniform ( "numLights" , ableLightNum );
	for ( int i = 0; i < ableLightNum; i++ ) {
		while ( !lightMass[ index ]->Switch_lightControl ( ) ) {
			index += 1;
		}

		std::string base = "lightTransform[" + std::to_string ( i ) + "]";

		auto view = lightMass[ index ]->GetlightView ( );
		auto proj = lightMass[ index ]->GetlightProjection ( );
		auto lightTransform = proj * view; // 라이트의 lightSpaceMatrix 계산

		glUniformMatrix4fv ( glGetUniformLocation ( program->Get() , ( base ).c_str ( ) ) , 1 , GL_FALSE , glm::value_ptr ( lightTransform ) );


		glActiveTexture ( GL_TEXTURE0 + 5 + i );
		base = "shadowMaps[" + std::to_string ( i ) + "]";
		lightMass[ index ]->GetlightShadowMap()->GetShadowMap ( )->Bind ( );
		// m_lightingShadowProgram->SetUniform ( "shadowMap[" + std::to_string ( i ) + "]" , 3+i );  // 각 라이트의 그림자 맵 바인딩
		glUniform1i ( glGetUniformLocation ( program->Get ( ) , ( base ).c_str ( ) ) , 5 + i );
		index += 1;
	}

	glActiveTexture ( GL_TEXTURE0 );
}

void LightManager::AddLight ( LightMass* addlight ) {
	lightMass.push_back ( addlight );
	LightNum = lightMass.size ( );
}
