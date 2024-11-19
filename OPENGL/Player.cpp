#include "Player.h"
#include "Time.h"
#include "Sound.h"

void Player::Update ( )
{
	Dir = camera->GetFront ( );
	camera->Camera_set ( Pos );
	camera->Camera_Ismoving ( Ismoving );
}

void Player::Render ( )
{
	//_shader->Use ( );
	//auto camerapos = CameraManager::getInstance ( ).GetPos ( );
	//auto view = CameraManager::getInstance ( ).GetView ( );
	//auto projection = CameraManager::getInstance ( ).GetProjection ( );

	//glm::vec3 direction = glm::normalize ( glm::vec3 ( 1.0f , 0.0f , 1.0f ) ); // 바라볼 방향
	//glm::vec3 up = glm::vec3 ( 0.0f , 1.0f , 0.0f ); // 업 벡터
	//glm::quat rotation = glm::quatLookAt ( direction , up );
	//glm::mat4 modelMatrix = glm::mat4_cast ( rotation );

	//modelTransform =
	//	glm::translate ( glm::mat4 ( 1.0f ) , Pos) *
	//	modelMatrix *
	//	glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 1.5f , 1.5f , 1.5f ) );
	//auto transform = projection * view * modelTransform;
	//_shader->SetUniform ( "modelTransform" , modelTransform );
	//_shader->SetUniform ( "transform" , transform );

	//_model->Draw ( _shader.get ( ) );
}

void Player::Initialize ( )
{
	camera = new Camera;

}

void Player::Input ( GLFWwindow* window ) {
	Ismoving = false;

	glm::vec3 cameraDirectionXZ = glm::normalize ( glm::vec3 ( Dir.x , 0.0f , Dir.z ) );
	auto cameraRight = glm::normalize ( glm::cross ( glm::vec3(0.0f,1.0f,0.0f) , cameraDirectionXZ ) );

	float speed = 10 * Time::DeltaTime ( );
	
	if ( glfwGetKey ( window , GLFW_KEY_W ) == GLFW_PRESS ) {
		Pos += speed * cameraDirectionXZ;
		Ismoving = true;
		//SoundManager::getInstance ( ).GetSoundID ( "charge" )->ReplaySound ( );
	}
	if ( glfwGetKey ( window , GLFW_KEY_S ) == GLFW_PRESS ) {
		Pos -= speed * cameraDirectionXZ;
		Ismoving = true;
	}

	if ( glfwGetKey ( window , GLFW_KEY_D ) == GLFW_PRESS ) {
		Pos -= speed * cameraRight;
		Ismoving = true;
	}
	if ( glfwGetKey ( window , GLFW_KEY_A ) == GLFW_PRESS ) {
		Pos += speed * cameraRight; 
		Ismoving = true;
	}


	if ( glfwGetKey ( window , GLFW_KEY_LEFT_CONTROL ) == GLFW_PRESS ) {
		Pos.y = 2;
	}
	if ( glfwGetKey ( window , GLFW_KEY_LEFT_CONTROL ) == GLFW_RELEASE ) {
		Pos.y = 4;
	}

}

