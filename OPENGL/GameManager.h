#pragma once
#include "common_include.h"
#include "shader.h"
#include "program.h"
#include "context.h"
#include "Scene.h"
#include "Gameobject.h"

class GameManager
{
private:
	std::vector <Scene*> Scenes;
	Scene* playing_Scene = nullptr;
	int playing_index = 0;

public:
	void Update ( );
	void Initialize ( );
	void FixedUpdate ( );
	void Render ( );
	void Run ( ) {
		Update ( );
		FixedUpdate ( );
		Render ( );
	}
};

