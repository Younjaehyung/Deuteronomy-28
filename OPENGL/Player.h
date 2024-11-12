#pragma once
#include "Gameobject.h"
#include "model.h"


class Player : public Gameobject
{
public:
	Player ( const std::string& name ){
		

	}

	virtual void Update ( );
	virtual void Render ( );
	virtual void Input ( GLFWwindow* window );
	virtual void MouseMove ( double x , double y );
	virtual void Initialize ( );
private:
	CameraManager* Camera;

	ModelUPtr _model;
	ProgramUPtr _shader;
	glm::mat4 modelTransform;
	glm::vec2 m_prevMousePos{ glm::vec2 ( 0.0f ) };
	glm::vec3 Pos = glm::vec3 ( 0.0f , 0.0f , 0.0f );	//위치
	glm::vec3 Dir = glm::vec3 ( 0.0f , 0.0f , 1.0f );	//방향
};

