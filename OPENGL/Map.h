#pragma once
#include "model.h"
#include "Animation.h"
#include "Animator.h"
#include "CameraManager.h"
#include "object.h"

class LightMass;
class Map :public Object
{
public:

	Map ( ) {
		typeID = 0;

	}

	virtual void Update ( );
	virtual void Render ( const Program* program );
	virtual void Initialize ( const std::string& strName );
	virtual void RenderShadow ( glm::mat4 lightView , const Program* program );
	
	
private:
	void CollisionLight ( );

	void SettingCamera ( );
	void SettingLight ( );

	UBOBUFFER_LIGHTUPtr UBO;

	std::vector<Camera*> mapCamera;
	std::vector<LightMass*> lightMass;
	glm::mat4 modelTransform;
	glm::vec2 m_prevMousePos{ glm::vec2 ( 0.0f ) };
	//glm::vec3 Pos = glm::vec3 ( 0.0f , 0.0f , 0.0f );	//위치
	//glm::vec3 Dir = glm::vec3 ( 0.0f , 0.0f , 1.0f );	//방향
	ModelPtr m_model;
	MeshUPtr ground;
	Animation* idleAnim;
	Animator* animator;
	ProgramUPtr _shader;
	

	Camera* camera1;
	std::vector<LightMass*> light;
	std::vector<Camera*> camera;
	

	LightMass* light1;
	LightMass* light2;
	LightMass* light3;
	LightMass* light4;
	LightMass* light5;
	LightMass* light6;
	LightMass* light7;
	LightMass* light8;
	LightMass* light9;
	LightMass* light10;
	LightMass* light11;
	LightMass* light12;
	LightMass* light13;
	LightMass* light14;

};

