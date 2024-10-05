#pragma once
#include "Component.h"

#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"

class PhysicsComponent : public Component {
private:
	bool _isGravity;
	float _gravity;
	glm::vec3 _acceleration;	//가속도
	glm::vec3 _velocity;	//속도

public:

	PhysicsComponent ( Gameobject* pOwner ,float gravity ) :Component(pOwner){
		_isGravity = false;
		_gravity = gravity;
		_acceleration = glm::vec3 ( 0 , 0 , 0 );
		_velocity = glm::vec3 ( 0 , 0 , 0 );
	}

	~PhysicsComponent ( ) {

	}



	void Update ( float deltaTime ) override {
		// 물리 처리
	}

	void SetIsGravity (bool Affected ) {
		_isGravity == Affected;
	}
	bool GetIsGravity ( ) {
		return _isGravity;
	}

	void SetGravity ( float value ) {
		_gravity = value;
	}
	float GetGravity ( ) const {
		return _gravity;
	}

	void SetAcceleration ( float x , float y , float z ) {
		_acceleration = glm::vec3 ( x , y , z );
	}

	const glm::vec3& GetAcceleration ( ) {
		return _acceleration;
	}


	void SetVelocity ( float x , float y , float z ) {
		_velocity = glm::vec3 ( x , y , z );
	}
	const glm::vec3& GetAccleration ( float x , float y , float z ) {
		return _velocity;
	}
};


