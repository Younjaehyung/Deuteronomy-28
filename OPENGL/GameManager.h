#pragma once
#include "common_include.h"
#include "shader.h"
#include "program.h"
#include "Scene.h"
#include "Sound.h"
#include "Time.h"
#include "input.h"

enum class gamemode {
	start,
	intro,
	play,
	Gameover,
	Gameend,
	Max
};

class GameManager
{

public:
	enum class Status {
		start ,
		running ,
		exit ,
	};

	int m_width{ 640 };
	int m_height{ 480 };

	void Update ( );
	void Initialize ( );
	void ProcessInput ( GLFWwindow* window );
	void MouseButton ( int button , int action , double x , double y );

	void FixedUpdate ( );
	void Render ( );

	void GameLogic ( );
	void Reshape ( int width , int height );

	void Run ( ) {
		Update ( );
		FixedUpdate ( );
		Render ( );
	}
private:
	Scene* Death;
	Scene* Life;
	Scene* overmode;
	int EndingNum = 0;
	std::vector<Scene*> Scenes;
	enum Status status = Status::start;
	enum gamemode prevmode = gamemode::start;
	enum gamemode mode = gamemode::play;
};

