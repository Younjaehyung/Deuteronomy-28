#pragma once
#include "Scene.h"
class Lifemap :public Scene
{

	ModelPtr m_map;
	ModelPtr m_player;
	Model* m_monster;

	Animation* monsterAnim;
	UBOBUFFERUPtr UBO;
	Animator* animator;

	Camera* mapCamera;
	std::vector<LightMass*> Visullight;


	ProgramUPtr m_program;
	ProgramUPtr m_simpleProgram;
	ProgramUPtr m_simpleAnimationProgram;
public:
	Lifemap ( ) {
		typeID = 0;
		std::cerr << "DEATH MAP Initialize " << std::endl;
		m_simpleProgram = Program::Create ( "./shader/lighting_shadow.vs" , "./shader/lighting_shadow.fs" );
		if ( !m_simpleProgram ) {
			std::cerr << "program UserSetError id : " << m_simpleProgram->Get ( ) << std::endl;
			return;


		}

		m_simpleAnimationProgram = Program::Create ( "./shader/animation.vs" , "./shader/animation.fs" );
		if ( !m_simpleAnimationProgram ) {
			std::cerr << "program UserSetError id : " << m_simpleAnimationProgram->Get ( ) << std::endl;
			return;


		}
		m_map = Model::Load ( "./model/DeathBox.glb" );

		UBO = UBOBUFFER::Create ( 200 );
		auto _monster = Model::Load ( "./model/HULK1/Hulk_Death.glb" );
		m_monster = _monster.get ( );
		monsterAnim = new Animation ( "./model/HULK1/Hulk_Death.glb" , m_monster );
		animator = new Animator ( monsterAnim );

		mapCamera = new Camera;

	}
	virtual void Update ( );
	virtual void Render ( );
	virtual bool Initialize ( );
	virtual int Check ( ) {
		return false;
	}

};

