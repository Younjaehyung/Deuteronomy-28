#pragma once
#include "Gameobject.h"
#include "model.h"
#include "Camera.h"

class Player
{
public:
	Camera* camera;
	
	Player ( ){
		

	}

	virtual void Update ( );
	virtual void Render ( );
	virtual glm::vec3& GetPos ( ) {
		return Pos;
	}
	virtual void Input ( GLFWwindow* window );
	virtual void Initialize ( );
private:

	ModelUPtr _model;
	ProgramUPtr _shader;

	glm::mat4 modelTransform;
	glm::vec2 m_prevMousePos{ glm::vec2 ( 0.0f ) };
	glm::vec3 Pos = glm::vec3 ( 0.0f , 0.0f , 5.0f );	//위치
	glm::vec3 Dir = glm::vec3 ( 0.0f , 0.0f , 1.0f );	//방향

	
};

