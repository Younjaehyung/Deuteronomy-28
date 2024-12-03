#pragma once
#include "model.h"
#include "Animation.h"
#include "Animator.h"
#include "CameraManager.h"
#include "object.h"
#include "LightMass.h"

class Deathmap :public Object
{
	ModelPtr m_model;
	Camera* mapCamera;
	std::vector<LightMass*> Visullight;

public:
	Deathmap ( glm::vec3 _pos ) {
		typeID = 0;
		Pos = _pos;
	}
	virtual void Update ( );
	virtual void Render ( const Program* program , glm::mat4 _cameraTransform );
	virtual void Initialize ( const std::string& strName );
	virtual void RenderShadow ( glm::mat4 lightView , const Program* program );

};

