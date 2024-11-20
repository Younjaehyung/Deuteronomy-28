#pragma once
#include "model.h"
#include "Camera.h"
#include "object.h"
#include "Animation.h"
#include "Animator.h"

class Player : public Object
{
public:
	Camera* camera;
	
	Player ( ){
		

	}

	virtual void Update ( );
	virtual void Status_Machine ( );
	virtual void Render ( const Program* program );
	virtual glm::vec3& GetPos ( ) {
		return Pos;
	}
	virtual void Input ( GLFWwindow* window );
	virtual void Initialize ( const std::string& strName = "" );
	

	

private:

	float running_stamina{ 10.0f };

	Model* model;
	ModelPtr _model;
	ProgramUPtr _shader;
	Animation* idleAnim;
	Animation* walkAnim;
	Animation* runAnim;
	Animation* sitwalkAnim;
	Animation* sitAnim;

	Animator* animator;
	UBOBUFFERUPtr UBO;

	enum moving movestat;

	glm::mat4 modelTransform;
	glm::vec2 m_prevMousePos{ glm::vec2 ( 0.0f ) };
	glm::vec3 Pos = glm::vec3 ( 0.0f , 0.0f , 0.0f );	//위치
	glm::mat4 Dir = glm::mat4(1.0f);	//방향
	glm::vec3 Dir2 = glm::vec3 ( 0.0f , 0.0f , -1.0f );	//방향
	//24: 4 = 맵 : 사람
	
};


