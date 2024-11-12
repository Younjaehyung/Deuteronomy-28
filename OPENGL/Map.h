#pragma once
#include "model.h"
#include "CameraManager.h"

class Map
{
public:

	Camera* camera;

	Map ( ) {


	}

	virtual void Update ( );
	virtual void Render ( const Program* program );
	virtual void Initialize ( const std::string& strName );
private:

	ModelUPtr _model;
	ProgramUPtr _shader;

	std::vector<Camera*> mapCamera;
	glm::mat4 modelTransform;
	glm::vec2 m_prevMousePos{ glm::vec2 ( 0.0f ) };
	glm::vec3 Pos = glm::vec3 ( 0.0f , 0.0f , 0.0f );	//위치
	glm::vec3 Dir = glm::vec3 ( 0.0f , 0.0f , 1.0f );	//방향


};

