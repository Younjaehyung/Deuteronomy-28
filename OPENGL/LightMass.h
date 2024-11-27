#pragma once
#include "shadow.h"
#include "object.h"
#include "framebuffer.h"
#include "shader.h"
#include "program.h"
#include "mesh_user.h"

class LightMass : public Object
{
private:
	bool m_lightControl{ false };
	std::string name;
	Light_ORI* lightData;
	glm::mat4 lightProjection;
	glm::mat4 lightView;
	ShadowMapPtr m_shadowMap = ShadowMap::Create ( 2048 , 2048 );
public:
	LightMass ( ) {
		lightData = new Light_ORI;
		lightProjection = glm::mat4 ( 1.0f );
		lightView = glm::mat4 ( 1.0f );
	}

	//void Update ( );




	void SetLight ( glm::vec3 pos , glm::vec3 dir , glm::vec2 cutoff );
	
	void SetSynLight ( glm::vec3 pos , glm::vec3 dir,glm::mat4 projection , glm::mat4 view);




	Light_ORI GetlightData ( ) {
		return *lightData;
	}

	glm::mat4 GetlightProjection ( ) {
		return lightProjection;
	};
	glm::mat4 GetlightView ( ) {
		return lightView;
	}
	ShadowMapPtr GetlightShadowMap ( ) {
		return m_shadowMap;
	}
	const std::string GetName ( ) {
		return name;
	}
	bool& Switch_lightControl ( ) {
		return m_lightControl;
	}
};

