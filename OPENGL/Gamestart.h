#pragma once
#include "Scene.h"

class Gamestart :public Scene
{
	ModelPtr m_model;
	Camera* mapCamera;
	std::vector<LightMass*> Visullight;

	ProgramUPtr m_program;
	ProgramUPtr m_simpleProgram;
	ProgramUPtr m_simpleAnimationProgram;

public:
	Gamestart ( ) {
		typeID = 0;

	}
	virtual void Update ( );
	virtual void Render ( );
	virtual void Initialize ();



};

