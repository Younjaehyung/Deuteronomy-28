#include "Player.h"
#include "Time.h"

void Player::Update ( )
{
	
}

void Player::Render ( )
{
	_shader->Use ( );
	auto camerapos = CameraManager::getInstance ( ).GetPos ( );
	auto view = CameraManager::getInstance ( ).GetView ( );
	auto projection = CameraManager::getInstance ( ).GetProjection ( );

	glm::vec3 direction = glm::normalize ( glm::vec3 ( 1.0f , 0.0f , 1.0f ) ); // 바라볼 방향
	glm::vec3 up = glm::vec3 ( 0.0f , 1.0f , 0.0f ); // 업 벡터
	glm::quat rotation = glm::quatLookAt ( direction , up );
	glm::mat4 modelMatrix = glm::mat4_cast ( rotation );

	modelTransform =
		glm::translate ( glm::mat4 ( 1.0f ) , Pos) *
		modelMatrix *
		glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 1.5f , 1.5f , 1.5f ) );
	auto transform = projection * view * modelTransform;
	_shader->SetUniform ( "modelTransform" , modelTransform );
	_shader->SetUniform ( "transform" , transform );

	_model->Draw ( _shader.get ( ) );
}

void Player::Initialize ( )
{
	

}

void Player::Input ( GLFWwindow* window ) {


	float speed = Time::DeltaTime ( );
	if ( glfwGetKey ( window , GLFW_KEY_W ) == GLFW_PRESS )
		Pos += speed * glm::vec3(0.0f,0.0f,-1.0f);
    if ( glfwGetKey ( window , GLFW_KEY_S ) == GLFW_PRESS )
		Pos += speed * glm::vec3 ( 0.0f , 0.0f , 1.0f );

    if ( glfwGetKey ( window , GLFW_KEY_D ) == GLFW_PRESS )
		Pos += speed * glm::vec3 ( 1.0f , 0.0f , 0.0f );
    if ( glfwGetKey ( window , GLFW_KEY_A ) == GLFW_PRESS );
		Pos += speed * glm::vec3 ( -1.0f , 0.0f , 0.0f );

		Camera->GetPos ( ) = Pos;
}

void Player::MouseMove ( double x , double y ) {

	auto pos = glm::vec2 ( ( float ) x , ( float ) y );
	auto deltaPos = pos - m_prevMousePos;

	const float cameraRotSpeed = 0.8f;
	Camera->m_cameraYaw -= deltaPos.x * cameraRotSpeed;
	Camera->m_cameraPitch -= deltaPos.y * cameraRotSpeed;

	if ( m_cameraYaw < 0.0f )   m_cameraYaw += 360.0f;
	if ( m_cameraYaw > 360.0f ) m_cameraYaw -= 360.0f;

	if ( m_cameraPitch > 89.0f )  m_cameraPitch = 89.0f;
	if ( m_cameraPitch < -89.0f ) m_cameraPitch = -89.0f;


	m_prevMousePos = pos;
}