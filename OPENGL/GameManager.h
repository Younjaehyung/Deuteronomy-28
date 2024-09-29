#pragma once
#include "common_include.h"
#include "shader.h"
#include "program.h"
#include "context.h"

#include "Gameobject.h"

class GameManager
{
private:


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

