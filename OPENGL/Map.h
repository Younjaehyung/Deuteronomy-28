#pragma once
#include "model.h"
#include "Animation.h"
#include "Animator.h"
#include "CameraManager.h"

class Map
{
public:

	Camera* camera;
	ModelPtr _model;
	MeshUPtr ground;
	Animation* idleAnim;
	Animator* animator;
	ProgramUPtr _shader;
	Map ( ) {


	}

	virtual void Update ( );
	virtual void Render ( const Program* program );
	virtual void Initialize ( const std::string& strName );
private:

	
	Model* model;
	std::vector<Camera*> mapCamera;
	glm::mat4 modelTransform;
	glm::vec2 m_prevMousePos{ glm::vec2 ( 0.0f ) };
	glm::vec3 Pos = glm::vec3 ( 0.0f , 0.0f , 0.0f );	//위치
	glm::vec3 Dir = glm::vec3 ( 0.0f , 0.0f , 1.0f );	//방향

	
};

