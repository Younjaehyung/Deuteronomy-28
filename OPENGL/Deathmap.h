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
	ModelPtr m_map;
	ModelPtr m_player;
	ModelPtr m_monster;

	Camera* mapCamera;
	std::vector<LightMass*> Visullight;

	ProgramUPtr m_program;
	ProgramUPtr m_simpleProgram;
	ProgramUPtr m_simpleAnimationProgram;
public:
	Deathmap () {
		typeID = 0;
		std::cerr << "DEATH MAP Initialize " << std::endl;
		m_simpleProgram = Program::Create ( "./shader/lighting_shadow.vs" , "./shader/lighting_shadow.fs" );
		if ( !m_simpleProgram ) {
			std::cerr << "program UserSetError id : " << m_simpleProgram->Get ( ) << std::endl;
			return;


		}

		m_simpleAnimationProgram = Program::Create ( "./shader/lighting_shadow.vs" , "./shader/lighting_shadow.fs" );
		if ( !m_simpleAnimationProgram ) {
			std::cerr << "program UserSetError id : " << m_simpleAnimationProgram->Get ( ) << std::endl;
			return ;


		}
	}
	virtual void Update ( );
	virtual void Render ( );
	virtual bool Initialize ();
	virtual int Check ( ) {
		return true;
	}

};

