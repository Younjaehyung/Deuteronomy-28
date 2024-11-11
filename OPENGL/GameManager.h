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
	std::vector <Gameobject*> Gameobjects;
	

public:
	void Update ( );
	void Initialize ( );
	void Input ( GLFWwindow* window );
	void FixedUpdate ( );
	void Render ( );
	void Run ( ) {
		Input ( );
		Update ( );
		FixedUpdate ( );
		Render ( );
	}
};

