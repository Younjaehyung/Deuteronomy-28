#include "Collision.h"
void Collision::Update ( )
{

}

void Collision::Initialize ( )
{

}

void Collision::SetBox ( Object* object ) {
	//glm::vec3 Dir = glm::normalize( glm::vec3(object->Dir2.x, 0.0f, object->Dir2.z) );
	glm::translate ( glm::mat4 ( 1.0f ) , object->Pos )* object->Dir;
	//glm::rotate ( glm::mat4 ( 1.0f ),glm::radians( object->Dir),glm::vec3(1.0f,0.0f,0.0f ));
}

void  Collision::Render ( ) {

}


void Collision::Observer ( ) {

}

void Collision::SetCollision(Object* collider_box ) {
	collider.push_back ( collider_box );
}

