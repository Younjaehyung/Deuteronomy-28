#pragma once
#include "shadow.h"
#include "object.h"
#include "framebuffer.h"
#include "shader.h"
#include "program.h"
#include "mesh_user.h"
class Player;
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
		std::string name;
		Light_ORI lightData;
		glm::mat4 lightProjection;
		glm::mat4 lightView;
		ShadowMapUPtr m_shadowMap = ShadowMap::Create (2048,2048 );
	};

	const int MAXLIGHTNUM =20;
	int LightNum = 0;
	UBOBUFFER_LIGHTPtr UBOLight;
	Program* m_simpleProgram =nullptr;
	Program* m_simpleAnimationProgram = nullptr;
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

	void Initialize (Program* program, Program* program2 ) {
		m_simpleProgram = program;
		m_simpleAnimationProgram = program2;
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

	void SetFlashLight ( Player* player );

	void UpdateFlashLight ( Player* player );

	void SetLight ( glm::vec3 pos , glm::vec3 dir , glm::vec2 cutoff );

};

