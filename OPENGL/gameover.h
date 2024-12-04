#pragma once
#include "Scene.h"
#include "model.h"
#include "object.h"
#include "Player.h"
#include "character.h"
#include "Map.h"

class gameover :public Scene
{
	ProgramUPtr m_program;
	ProgramUPtr m_simpleProgram;
	ProgramUPtr m_simpleAnimationProgram;

	Map* map;
	Player* player;
	character* object1;		//Neddlehead

public:
	virtual void Update ( );
	virtual bool Initialize ( );
	virtual void ProcessInput ( );
	virtual void FixedUpdate ( );
	virtual void Render ( );
};	

