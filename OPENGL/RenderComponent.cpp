#include "RenderComponent.h"
#include "Gameobject.h"	//상호참조를 막기 위해 여기다가 include 함
//glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( 40.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) ) *
void RenderComponent::Update(){
    modelTransform =
        glm::translate ( glm::mat4 ( 1.0f ) , GenOwner()->GetPos() ) *
        GenOwner()->GetDir()*
        glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 1.5f , 1.5f , 1.5f ) );
}