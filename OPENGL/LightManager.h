#pragma once
#include "shadow.h"
#include "object.h"
#include "framebuffer.h"
#include "shader.h"
#include "program.h"
#include "mesh_user.h"
class LightManager
{
	//struct Light {
	//	bool directional{ false };

	//	glm::vec3 direction{ glm::vec3 ( -0.2f, -1.0f, -0.3f ) };	//Directional Light
	//	glm::vec2 cutoff{ glm::vec2 ( 20.0f, 5.0f ) };	//Spot Light 보이는 부분
	//	float distance{ 232.0f }; //Point Light 감쇠 거리

	//	glm::vec3 position{ glm::vec3 ( 3.0f, 3.0f, 3.0f ) }; //광원의 위치
	//	glm::vec3 ambient{ glm::vec3 ( 0.0f, 0.0f, 0.0f ) };  //광원의 색
	//	glm::vec3 diffuse{ glm::vec3 ( 1.0f, 1.0f, 1.0f ) };  //오브젝트의 색
	//	glm::vec3 specular{ glm::vec3 ( 1.0f, 1.0f, 1.0f ) };
	//};

	struct LightMass {
		Light_ORI lightData;
		glm::mat4 lightProjection;
		glm::mat4 lightView;
		ShadowMapUPtr m_shadowMap = ShadowMap::Create (2048,2048 );
	};

	const int MAXLIGHTNUM =20;
	int LightNum = 0;
	UBOBUFFER_LIGHTPtr UBOLight;
	Program* m_simpleProgram =nullptr;
	std::vector<LightMass*> lightMass;
	std::vector<Light_ORI> m_lights;
	LightManager ( ) {

	}
public:
	static LightManager& getInstance ( ) {
		static LightManager instance;
		return instance;
	}

	void UpdateShadowMaps ( const std::vector<Object*>& sceneObjects );
	void GetLightSetting ( const Program* programs );
	void UpdateShadowMapping ( const Program* program );

	void Initialize (Program* program ) {
		m_simpleProgram = program;

		UBOLight = UBOBUFFER_LIGHT::Create ( MAXLIGHTNUM );

	}

	int GetLightNum ( ) {
		return LightNum;
	}

	glm::mat4 GetLightTransform ( int i ) {
		return lightMass[i]->lightProjection * lightMass[ i ]->lightView;
	}

	ShadowMap* GetShadowMap ( int i ) {
		return lightMass[ i ]->m_shadowMap.get();
	}


	UBOBUFFER_LIGHTPtr GetLight ( ) {
		return UBOLight;
	}


	void SetLight ( glm::vec3 pos , glm::vec3 dir , glm::vec2 cutoff ) {
		LightMass* lighting = new LightMass;
		lighting->lightView= glm::lookAt ( pos ,pos + dir ,glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
		lighting->lightData.directional = 0;
		lighting->lightProjection = glm::perspective (
	  glm::radians ( ( cutoff[ 0 ] + cutoff[ 1 ] ) * 2.0f ) ,1.0f , 1.0f , 20.0f );
		lighting->lightData.position = pos;
		lighting->lightData.direction = dir;
		lighting->lightData.cutoff = glm::vec2 (
		cosf ( glm::radians (cutoff[ 0 ])  ) ,cosf ( glm::radians (cutoff[ 0 ] +cutoff[ 1 ]))  );

		lighting->lightData.attenuation = GetAttenuationCoeff ( 200.0f );
		lighting->lightData.ambient = glm::vec3 ( 1.0f , 1.0f , 1.0f );
		lighting->lightData.diffuse = glm::vec3 ( 1.0f );
		lighting->lightData.specular = glm::vec3 ( 1.0f , 1.0f , 1.0f );

		m_lights.push_back ( lighting->lightData );
		lightMass.push_back ( lighting );
		LightNum = m_lights.size ( );

	}

};

