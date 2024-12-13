#pragma once
#include "model.h"
#include "Animation.h"
#include "Animator.h"
#include "CameraManager.h"
#include "object.h"
#include "LightMass.h"
#include "Scene.h"

class Deathmap :public Scene
{
	struct DeathmapLight {
		

		glm::vec3 direction{0,0,0}; //태양광(모든 지점에 동일한 방향의 광선/Directional Light, Spot Light)

			glm::vec3 attenuation = GetAttenuationCoeff ( 90.0f );; //광원의 빛 감쇠 계산식(Point Light, Spot Light)

			glm::vec2 cutoff{ glm::vec2 ( 20.0f, 5.0f ) };    //광원의 빛 범위(Spot Light)

			glm::vec3 position{0,10,0};  //광원의 위치
			glm::vec3 ambient{0,0,0};   //주변광의 색상
			glm::vec3 diffuse{255,255,255};   //확산광의 색상
			glm::vec3 specular{255,255,255};  //반사광의 색상
		
	};
	DeathmapLight light;

	ModelPtr m_map;
	ModelPtr m_player;
	Model* m_monster;

	Animation* monsterAnim;
	UBOBUFFERUPtr UBO;
	Animator* animator;

	Camera* mapCamera;
	//std::vector<LightMass*> Visullight;
	

	ProgramUPtr m_program;
	ProgramUPtr m_simpleProgram;
	ProgramUPtr m_simpleAnimationProgram;
public:
	Deathmap () {
		typeID = 0;
		std::cerr << "DEATH MAP Initialize " << std::endl;
		m_simpleProgram = Program::Create ( "./shader/lighting.vs" , "./shader/lighting.fs" );
		if ( !m_simpleProgram ) {
			std::cerr << "program UserSetError id : " << m_simpleProgram->Get ( ) << std::endl;
			return;


		}

		m_simpleAnimationProgram = Program::Create ( "./shader/animation.vs" , "./shader/animation.fs" );
		if ( !m_simpleAnimationProgram ) {
			std::cerr << "program UserSetError id : " << m_simpleAnimationProgram->Get ( ) << std::endl;
			return ;

			
		}
		m_map = Model::Load ("./model/DeathBox.glb" );
		
		UBO = UBOBUFFER::Create ( 200 );
		auto _monster = Model::Load ( "./model/HULK1/Hulk_Death.glb"  );
		m_monster = _monster.get ( );
		monsterAnim = new Animation ( "./model/HULK1/Hulk_Death.glb" , m_monster );
		animator = new Animator ( monsterAnim );

		mapCamera = new Camera;
		
	}
	virtual void Update ( );
	virtual void Render ( );
	virtual bool Initialize ();
	virtual int Check ( ) {
		return false;
	}

};

