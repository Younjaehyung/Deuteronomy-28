#pragma once

#include "model.h"
#include "Animation.h"
#include "Animator.h"
#include "CameraManager.h"
#include "Astar.h"

enum class Phase {
	Idle,
	Angry,
	Mad,
	Crazy,
};

enum class Action {
	Idle ,
	running ,
	walk ,
	attack,
	scream,
};

enum class Status {
	start ,
	running ,
	exit ,
};


class character : public Object
{
public:
	Collision* collision;
	Camera* camera;
	

	character (glm::vec3 pos) {
		typeID = 1;
		Pos = pos;
		objectID = eLayerType::Enemy;
	}

	virtual void Update ( );
	virtual bool HandleCollision ( Object* object );
	virtual void Render_2pass ( const Program* program, glm::mat4 _cameraTransform );
	virtual void Render ( const Program* program );
	virtual void Initialize ( const std::string& strName );
	virtual void RenderShadow ( glm::mat4 lightView , const Program* program );
	
	int GetPhase ( ) {
		if ( phase == Phase::Mad ) {
			return 2;
		}
		else if ( phase == Phase::Angry ) {
			return 1;
		}
		else {
			return 0;
		}
		
	}
	bool DynamicAlgorithm ( );
	bool StaticAlgorithm (glm::ivec2 _path );
	void Status_Machine ( );

	void notifyFromMap (glm::vec3 where, int alert = 0) {
		if ( alert == 0 && chase ==0 ) {
			if ( phase == Phase::Idle ) {
				Path_now( where , chaseWhere );
				phase = Phase::Angry;
				action = Action::running;
				status = Status::start;
				chase = 1;
				std::cout << "IDLE LIGHT EVENT!" << std::endl;
			}
			else if ( phase == Phase::Angry && chase == 0 ) {
				phase = Phase::Mad;
				action = Action::running;
				status = Status::start;
				chase = 1;
				std::cout << "ANGRY LIGHT EVENT!" << std::endl;
			}
		}
		else if ( alert == 1 ) {
			phase = Phase::Crazy;
		}

	}
	


private:

	void Path_now ( glm::vec3 Pos , glm::ivec2& path_now ) {
		//float dul = Pos.x - int ( Pos.x );

		path_now.x = ( int ( Pos.x ) - ( int ( Pos.x ) % 3 ) ) / 3;
		// Z축 인덱스 계산
		path_now.y = ( int ( Pos.z ) / 3 ) * 1; // 기본적으로 3의 배수로 변환
		if ( Pos.z > 0 && int ( Pos.z ) % 3 != 0 ) {
			path_now.y += 1; // 양수 방향 보정

		}
		path_now.y = -path_now.y;


		if ( Pos.x < 0 ) {
			path_now.x -= 1;

		}



		//std::cout << "path_now_x : " << path_now.x << std::endl;
		//std::cout << "path_now_z : " << path_now.y << std::endl;
	}

	void Path_now ( ) {
		//float dul = Pos.x - int ( Pos.x );

		path_now_x = ( int ( Pos.x ) - ( int ( Pos.x ) % 3 ) ) / 3;
		// Z축 인덱스 계산
		path_now_z = ( int ( Pos.z ) / 3 ) * 1; // 기본적으로 3의 배수로 변환
		if ( Pos.z > 0 && int ( Pos.z ) % 3 != 0 ) {
			path_now_z += 1; // 양수 방향 보정

		}
		path_now_z = -path_now_z;


		if ( Pos.x < 0 ) {
			path_now_x -= 1;

		}



		//std::cout << "path_now_x : " << path_now_x << std::endl;
		//std::cout << "path_now_z : " << path_now_z << std::endl;
		//std::cout <<"iint pos"<< int ( Pos.x ) << std::endl;
	}

	ModelPtr _model;
	Animation* idleAnim;
	Animation* attackAnim;
	Animation* runAnim;
	Animation* walkAnim;
	Animation* sceramAnim;

	Animator* animator;
	ProgramUPtr _shader;
	UBOBUFFERUPtr UBO;

	Astar* algorithm = new Astar;
	std::vector<std::vector<int>> grid = {
			{0, 0, 0, 1, 0},
			{0, 1, 0, 1, 0},
			{0, 0, 0, 0, 0},
			{1, 1, 1, 0, 1},
			{0, 0, 0, 0, 0}
	};
	int pathindex = 0;
	std::tuple<int , int> gotoPath;
	int path_now_x;
	int path_now_z;

	
	Model* model;
	std::vector<Camera*> mapCamera;
	glm::mat4 modelTransform;
	glm::vec2 m_prevMousePos{ glm::vec2 ( 0.0f ) };
	//glm::vec3 Object::Pos = glm::vec3 ( 0.0f , 0.0f , 0.0f );	//위치
	//glm::vec3 Dir = glm::vec3 ( 0.0f , 0.0f , 1.0f );	//방향
	glm::vec3 Dir2 = glm::vec3 ( 0.0f , 0.0f , -1.0f );	//방향
	glm::quat quaternion;

	enum Status status = Status::start;
	enum Action action = Action::Idle;
	enum Phase phase = Phase::Idle;

	glm::ivec2 chaseWhere;
	int chase = 0;
	float time = 0.0f;
};

