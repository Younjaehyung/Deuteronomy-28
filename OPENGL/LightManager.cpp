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
		m_simpleProgram->Use ( );

		m_simpleProgram->SetUniform ( "color" , glm::vec4 ( 1.0f , 1.0f , 1.0f , 1.0f ) );


		std::cout <<"AAA" << sizeof ( glm::vec3 ) << std::endl;
		// 모든 오브젝트를 쉐도우맵에 렌더링
		for ( auto* object : sceneObjects ) {
			object->RenderShadow ( light->lightProjection * light->lightView, m_simpleProgram );
		}

		Framebuffer::BindToDefault ( );
	}

	glDisable ( GL_CULL_FACE );


}