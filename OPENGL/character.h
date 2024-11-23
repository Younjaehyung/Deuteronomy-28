#pragma once

#include "model.h"
#include "Animation.h"
#include "Animator.h"
#include "CameraManager.h"
#include "Astar.h"
class character : public Object
{
public:

	Camera* camera;
	ModelPtr _model;
	Animation* idleAnim;
	Animator* animator;
	ProgramUPtr _shader;
	UBOBUFFERUPtr UBO;

	character ( ) {


	}

	virtual void Update ( );
	
	virtual void Render ( const Program* program );
	virtual void Initialize ( const std::string& strName );
	virtual void Algorithm ( );
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



		std::cout << "path_now_x : " << path_now_x << std::endl;
		std::cout << "path_now_z : " << path_now_z << std::endl;
		//std::cout <<"iint pos"<< int ( Pos.x ) << std::endl;
	}
private:

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
};