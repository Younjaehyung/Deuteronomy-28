#pragma once
//#include "common_include.h"
//#include "shader.h"
//#include "program.h"
//#include "context.h"
#include "input.h"
//#include "Gameobject.h"
#include "Scene.h"

class GameManager
{
private:
	std::vector <Scene*> Scenes;
public:
	void Update ( );
	void Initialize ( );
	void FixedUpdate ( );
	void AddScene ( Scene* _scene );
	void Render ( );
	void Run ( ) {
		Update ( );
		FixedUpdate ( );
		Render ( );
	}
};

