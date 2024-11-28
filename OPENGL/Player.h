#pragma once
#include "model.h"
#include "LightMass.h"
#include "Camera.h"
#include "object.h"
#include "Animation.h"
#include "Animator.h"
#include "Collision.h"
#include "Item.h"

class Player : public Object
{
public:
	Camera* camera;
	LightMass* FlashLight;


	Player ( ){
		typeID = 1;
		objectID = eLayerType::Player;
	}

	virtual void Update ( );
	virtual void Status_Machine ( );
	virtual void Render ( const Program* program );
	virtual void RenderShadow ( glm::mat4 lightView , const Program* program );
	virtual void HandleCollision ( Object* object );
	virtual void Input ( GLFWwindow* window );
	virtual void Initialize ( const std::string& strName = "" );


	bool IsFlashLight ( ) {
		return FlashLight_switch;
;
	}

	glm::vec3 GetDir2 ( ) {
		return Dir2;
	}

	void Path_now ( ) {
		float dul = Pos.x - int ( Pos.x );
		
		int path_now_x = ( int ( Pos.x ) - ( int ( Pos.x ) % 3 ) ) / 3;
		// Z축 인덱스 계산
		int path_now_z = ( int ( Pos.z ) / 3 ) * 1; // 기본적으로 3의 배수로 변환
		if ( Pos.z > 0 && int ( Pos.z ) % 3 != 0 ) {
			path_now_z += 1; // 양수 방향 보정
			
		}
		path_now_z = -path_now_z;


		if ( Pos.x < 0 ) {
			path_now_x -= 1;
			
		}



			//std::cout <<"path_now_x : "<< path_now_x << std::endl;
			//std::cout << "path_now_z : " << path_now_z << std::endl;
			//std::cout <<"iint pos"<< int ( Pos.x ) << std::endl;
	}

	

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

	bool FlashLight_switch{ true };

	std::vector<Item*> Inventory;

	glm::mat4 modelTransform;
	glm::vec2 m_prevMousePos{ glm::vec2 ( 0.0f ) };
	//glm::vec3 Pos = glm::vec3 ( 0.0f , 0.0f , 0.0f );	//위치
	//glm::mat4 Dir = glm::mat4(1.0f);	//방향
	glm::vec3 Dir2 = glm::vec3 ( 0.0f , 0.0f , -1.0f );	//방향
	//24: 4 = 맵 : 사람
	

	
};


