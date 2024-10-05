#pragma once
#include "Gameobject.h"

class PlayerInputComponent;


class character : public Gameobject{

public:
	character ( ) {
		AddComponent<PlayerInputComponent> ( );


		AddComponent<RenderComponent> (
		this ,
		glm::translate ( glm::mat4 ( 1.0f ) , GetPos ( ) ) * glm::rotate ( glm::vec3 ( 0.0f , 0.0f , -1.0f ) , GetDir ( )  )
		,
		Model::Load ( "./model/FOX_GIRL/FOX_GIRL.obj" ) ,
		Program::Create ( "./shader/lighting.vs" , "./shader/lighting.fs" ) );

		
	}

	
private:



};

glm::vec3 position = GetPos ( );  // vec3 위치
glm::vec3 direction = GetDir ( );  // vec3 방향

// 방향을 쿼터니언으로 변환 (필요한 경우)
glm::quat rotation = glm::rotate ( glm::vec3 ( 0.0f , 0.0f , -1.0f ) , GetDir ( ) ); // Z축 기준으로 회전

// 변환 행렬 생성
glm::mat4 transform = 