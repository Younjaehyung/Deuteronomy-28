#include "Camera.h"
#include "Time.h"
std::random_device rd;
std::mt19937 gen ( rd ( ) );
std::uniform_real_distribution<float> camera_moving ( -5.0f , 5.0f );

const float camera_float = 0.2f;

void Camera::Update ( ) {
	



	if (! (m_TcameraYaw - 0.2f <= m_cameraYaw && m_cameraYaw <= m_TcameraYaw + 0.2f )) {
		m_cameraYaw -= deltaPos.x * 0.1f;
	}
	else {
		m_cameraYaw = m_TcameraYaw;
	}
	if (!( m_TcameraPitch - 0.2f <= m_cameraPitch && m_cameraPitch <= m_TcameraPitch + 0.2f )) {
		m_cameraPitch -= deltaPos.y * 0.1f;
	}
	else {
		m_cameraPitch = m_TcameraPitch;
	}




	//Debugging ( );
	float m_cameraPitch_movingR{ 0.0f };//뛸때 화면 흔들림
	float m_cameraPitch_moving{ 0.0f };//뛸때 화면 흔들림

	//std::cout << "m_cameraPitch_moving :"  << m_cameraPitch_moving << std::endl;
	if ( Ismoving == moving::run) {
		m_cameraPitch_moving = .8f*cos( 10.0f * moving_Time );
		m_cameraYaw += .1f * cos ( 10.0f * moving_Time );
		moving_Time += Time::DeltaTime ( );
		
	}
	else if (!(Ismoving == moving::run) ){
		//m_cameraPitch_moving = 0.0f;
		m_cameraPitch_moving = 2.0f * sin ( moving_Time );
		//moving_Time = 0;
		moving_Time += Time::DeltaTime ( );
	}




	if ( !static_camera ) {
		//m_cameraPitch_moving = glm::clamp ( m_cameraPitch_moving , -89.0f , 89.0f );
		m_cameraFront =
			glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( m_cameraPitch_moving ) , glm::vec3 ( 0.0f , 0.0f , 0.0f ) ) *
			 glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( m_cameraYaw ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) )
			* glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( m_cameraPitch ) , glm::vec3 ( 1.0f , 0.0f , 0.0f ) )
			* glm::vec4 ( 0.0f , 0.0f , -1.0f , 0.0f );   //방향벡터에는 4번째 항에 0을 넣음
		

		// 쿼터니언 생성
		glm::vec3 front = glm::vec3 ( 0.0f , 0.0f , -1.0f );
		glm::quat pitchQuat = glm::angleAxis ( glm::radians ( m_cameraPitch ) , glm::vec3 ( 1.0f , 0.0f , 0.0f ) );
		glm::quat yawQuat = glm::angleAxis ( glm::radians ( m_cameraYaw ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
		glm::quat rollQuat = glm::angleAxis ( glm::radians ( m_cameraPitch_moving ) , glm::vec3 ( 1.0f , 0.0f , 0.0f ) );
		// 쿼터니언 결합
		glm::quat orientation = yawQuat * pitchQuat* rollQuat;

		// 방향 벡터 변환
		m_cameraFront =  orientation *front ;
		view = glm::lookAt ( m_cameraPos , m_cameraPos + m_cameraFront , m_cameraUp );
	}
	else {
		view = glm::lookAt ( m_cameraPos , m_cameraPos + m_cameraFront , m_cameraUp );
	}

	projection = glm::perspective ( glm::radians ( SightAngle ) , ( float ) Height / ( float ) Widht , SightNear , SightFar );   //원근투영

	
	
}

void Camera::MouseMove ( double x , double y ) {


	auto pos = glm::vec2 ( ( float ) x , ( float ) y );
	deltaPos = pos - m_prevMousePos;



	const float cameraRotSpeed = 0.2f;
	m_TcameraYaw -= deltaPos.x * cameraRotSpeed;
	m_TcameraPitch -= deltaPos.y * cameraRotSpeed;


	if ( m_cameraYaw < 0.0f )   m_cameraYaw += 360.0f;
	if ( m_cameraYaw > 360.0f ) m_cameraYaw -= 360.0f;

	if ( m_cameraPitch > 89.0f )  m_cameraPitch = 89.0f;
	if ( m_cameraPitch < -89.0f ) m_cameraPitch = -89.0f;



		//glm::vec2 pos{ ( float ) x, ( float ) y };
		//glm::vec2 delta = pos - m_prevMousePos;
		//m_prevMousePos = pos;

		//m_yawTarget = WrapDeg ( m_yawTarget - delta.x * m_mouseSensitivity );
		//m_pitchTarget = std::clamp ( m_pitchTarget - delta.y * m_mouseSensitivity , -89.f , 89.f );
	




}

void Camera::SetCamera ( glm::vec3 _pos , glm::vec3 _dir , glm::vec3 _up , float Near, float Far , float Angle ) {

	m_cameraPos = _pos;
	static_camera = 1;
	// 카메라가 바라보는 방향 벡터 계산 (정규화)
	m_cameraFront = glm::normalize ( _dir -  _pos );

	// 카메라의 오른쪽 벡터 계산
	glm::vec3 m_cameraRIGHT = glm::normalize ( glm::cross ( _up , m_cameraFront ) );

	// 카메라의 위쪽 벡터 재계산 (정규화)
	m_cameraUp = glm::normalize ( glm::cross ( m_cameraFront, m_cameraRIGHT ) );

	// 뷰 행렬 생성
	view = glm::lookAt ( m_cameraPos , _pos + m_cameraFront , m_cameraUp );
	SightNear = Near;
	SightFar = Far;
	SightAngle = Angle;

	projection = glm::perspective ( glm::radians ( SightAngle ) , ( float ) Height / ( float ) Widht , SightNear , SightFar );   //원근투영

}