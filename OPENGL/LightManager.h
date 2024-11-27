#pragma once
#include "shadow.h"
#include "object.h"
#include "framebuffer.h"
#include "shader.h"
#include "program.h"
#include "mesh_user.h"
#include "LightMass.h"

class Player;
class LightManager
{

	const int MAXLIGHTNUM =20;//최대 빛 개수
	int LightNum = 0;//전체 빛 개수
	int ableLightNum = 0;//활성 빛 개수
	UBOBUFFER_LIGHTPtr UBOLight;
	Program* m_simpleProgram =nullptr;
	Program* m_simpleAnimationProgram = nullptr;
	std::vector<LightMass*> lightMass;//빛 

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
	void AddLight ( LightMass* addlight );

	void Initialize (Program* program, Program* program2 ) {
		m_simpleProgram = program;
		m_simpleAnimationProgram = program2;
		UBOLight = UBOBUFFER_LIGHT::Create ( MAXLIGHTNUM );
		
	}

	int GetLightNum ( ) {
		return LightNum;
	}


	UBOBUFFER_LIGHTPtr GetLight ( ) {
		return UBOLight;
	}


};

