#pragma once

class Gameobject;
#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"


class Component {
public:
	Component ( Gameobject* pOwner ) { m_pOwner = pOwner; }
	virtual ~Component ( ) = default;

	virtual void Update ( float deltaTime ) = 0;
	virtual void FixedUpdate ( ) = 0;
	virtual void Render ( glm::mat4 projection, glm::mat4 view ) = 0;


	//리턴값
	Gameobject* GenOwner( ) { return m_pOwner; }
	//const Gameobject* GetOwner ( ) const { return m_pOwner; }

private:
	Gameobject* m_pOwner = nullptr;	//Gameobject 자료형.
};



