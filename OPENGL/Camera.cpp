#include "Camera.h"
#include "Time.h"
std::random_device rd;
std::mt19937 gen ( rd ( ) );
std::uniform_real_distribution<float> camera_moving ( -5.0f , 5.0f );

const float camera_float = 0.2f;

void Camera::Update ( ) {
	
	Debugging ( );
	//std::cout << "m_cameraPitch_moving :"  << m_cameraPitch_moving << std::endl;
	if ( Ismoving == moving::run) {
		m_cameraPitch_moving = 5.0f*cos( 10.0f * moving_Time );
		moving_Time += Time::DeltaTime ( );
		
	}
	else if (!(Ismoving == moving::run) ){
		//m_cameraPitch_moving = 0.0f;
		m_cameraPitch_moving = 2.0f * sin ( moving_Time );
		//moving_Time = 0;
		moving_Time += Time::DeltaTime ( );
	}

	
	m_cameraFront =
		glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( m_cameraPitch_moving ) , glm::vec3 ( 1.0f , 0.0f , 0.0f ) )*
		glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( m_cameraPitch_moving ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) )
		* glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( m_cameraYaw ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) )
		* glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( m_cameraPitch ) , glm::vec3 ( 1.0f , 0.0f , 0.0f ) )
		* glm::vec4 ( 0.0f , 0.0f , -1.0f , 0.0f );   //방향벡터에는 4번째 항에 0을 넣음


	projection = glm::perspective ( glm::radians ( SightAngle ) , ( float ) Height / ( float ) Widht , SightNear , SightFar );   //원근투영

	//카메라 위치 함수
	view = glm::lookAt ( m_cameraPos , m_cameraPos + m_cameraFront , m_cameraUp );
}

void Camera::MouseMove ( double x , double y ) {
	



	auto pos = glm::vec2 ( ( float ) x , ( float ) y );
	auto deltaPos = pos - m_prevMousePos;

	const float cameraRotSpeed = 0.6f;
	m_cameraYaw -= deltaPos.x * cameraRotSpeed;
	m_cameraPitch -= deltaPos.y * cameraRotSpeed;

	if ( m_cameraYaw < 0.0f )   m_cameraYaw += 360.0f;
	if ( m_cameraYaw > 360.0f ) m_cameraYaw -= 360.0f;

	if ( m_cameraPitch > 89.0f )  m_cameraPitch = 89.0f;
	if ( m_cameraPitch < -89.0f ) m_cameraPitch = -89.0f;





}