#pragma once
#include "Scene.h"
#include "input.h"

class Gamestart :public Scene
{
	ModelPtr m_model;
	MeshUPtr m_plane;
	TextureUPtr Main1UITEXTURE;
	TextureUPtr MainStartTEXTURE;
	TextureUPtr Main2UITEXTURE;
	TextureUPtr Main3UITEXTURE;
	TextureUPtr Main4UITEXTURE;

	bool StartEngine{ false };
	int soundToggle = 0;
	Camera* mapCamera;
	std::vector<LightMass*> Visullight;

	ProgramUPtr m_program;
	ProgramUPtr m_simpleProgram;
	ProgramUPtr m_simpleAnimationProgram;
	ProgramUPtr m_camerauiProgram;

public:
	Gamestart ( ) {
		typeID = 0;
		Initialize ( );
	}
	virtual void Update ( );
	virtual void Render ( );
	virtual bool Initialize ();
	virtual void ProcessInput ( GLFWwindow* window )
	{
		if ( input::GetKeyDown ( eKeyCode::SPACE ) ) {
			StartEngine = 1;
		}
	}
	float startTime = 0.0f;
	virtual int Check ( ) {
		if ( StartEngine ) {
			std::cout << "나는 정왕의 신 오승원이다" << std::endl;
			return true;
		}

		return false;
	}


};

