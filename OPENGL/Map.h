#pragma once
#include "model.h"
#include "Animation.h"
#include "Animator.h"
#include "CameraManager.h"
#include "object.h"
#include "LightMass.h"
class character;


struct SightLight {

	Camera* mapCamera;

	std::vector<LightMass*> CollisionLight;
	std::vector<LightMass*> Visullight;

};


class Map :public Object
{
public:

	Map ( character* _monster ) {
		typeID = 0;
		monster = _monster;
	}

	virtual void Update ( );
	virtual void Render ( const Program* program , glm::mat4 _cameraTransform );
	virtual void Initialize ( const std::string& strName );
	virtual void RenderShadow ( glm::mat4 lightView , const Program* program );
	void ObjectInitialize ( std::vector<Object*>& gameobj) {
		for ( auto& obj : sightLight ) {
			for ( auto& _obj : obj->CollisionLight ) {
				gameobj.push_back ( _obj );
			}
		}
		for ( auto& obj : Wall ) {
			
			gameobj.push_back ( obj );
			
		}

	}

private:
	void CollisionLight ( );

	void SettingCamera ( );
	void SettingWall ( );
	void CameraLightUpdate ( );

	UBOBUFFER_LIGHTUPtr UBO;

	glm::mat4 modelTransform;
	glm::vec2 m_prevMousePos{ glm::vec2 ( 0.0f ) };
	//glm::vec3 Pos = glm::vec3 ( 0.0f , 0.0f , 0.0f );	//위치
	//glm::vec3 Dir = glm::vec3 ( 0.0f , 0.0f , 1.0f );	//방향
	ModelPtr m_model;
	MeshUPtr ground;
	Animation* idleAnim;
	Animator* animator;
	ProgramUPtr _shader;

	int usingCameraID = 0;
	float updateSightTime = 0.0f;
	std::vector<LightMass*> normalLight;
	std::vector<SightLight*> sightLight;
	std::vector<Object*> Wall;
	character* monster;



};

