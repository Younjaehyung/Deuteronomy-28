#pragma once
#include "Scene.h"
class Gameintro : public Scene
{
	struct Light {

		glm::vec3 direction; //태양광(모든 지점에 동일한 방향의 광선/Directional Light, Spot Light)

		glm::vec3 attenuation; //광원의 빛 감쇠 계산식(Point Light, Spot Light)

		glm::vec2 cutoff;    //광원의 빛 범위(Spot Light)

		glm::vec3 position;  //광원의 위치
		glm::vec3 ambient;   //주변광의 색상
		glm::vec3 diffuse;   //확산광의 색상
		glm::vec3 specular;  //반사광의 색상
	};

	MeshUPtr ground;
	ModelPtr m_model;
	ModelPtr m_car;
	MeshUPtr m_plane;
	TextureUPtr MainUITEXTURE;


	Camera* mapCamera;
	std::vector<LightMass*> Visullight;

	ProgramUPtr m_program;
	ProgramUPtr m_simpleProgram;
	ProgramUPtr m_simpleAnimationProgram;
	ProgramUPtr m_camerauiProgram;

	Object* car;

	int soundToggle = 0;
	int StartGame = 0;
	int status = 0;
public:
	Gameintro ( ) {
		typeID = 0;
		car = new Object;
		Initialize ( );
	}
	virtual void Update ( );
	virtual void Render ( );
	virtual bool Initialize ( );
	virtual void ProcessInput ( GLFWwindow* window );

	virtual int Check ( ) {


		return StartGame;
	}


};

