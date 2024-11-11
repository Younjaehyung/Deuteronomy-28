#pragma once
#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"

class CameraManager {

private:
	bool m_cameraControl;
	glm::vec2 m_prevMousePos{ glm::vec2 ( 0.0f ) };

	//카메라
	float m_cameraPitch{ 0.0f };
	float m_cameraYaw{ 0.0f };

	glm::vec3 m_cameraPos{ glm::vec3 ( 0.0f, 0.5f, 3.0f ) };	//카메라의 위치
	glm::vec3 m_cameraFront{ glm::vec3 ( 0.0f, 0.0f, -1.0f ) };	//카메라가 보고 있는 방향
	glm::vec3 m_cameraUp{ glm::vec3 ( 0.0f, 1.0f, 0.0f ) };		//카메라 up벡터


	glm::mat4 view;
	glm::mat4 projection;

	float SightNear=0.1f;
	float SightFar=300.0f;
	float SightAngle = 45.0f;

	float Widht=800.f;
	float Height = 600.f;
	

	CameraManager ( ) {

	}
public:
	static CameraManager& getInstance ( ) {
		static CameraManager instance;
		return instance;
	}


	void Update (glm::vec3 deltaPos, glm::vec3 rotate ) {
		m_cameraPos += deltaPos;


		CameraCalcul ( );

	}

	void MouseMove ( double x , double y ) {
		if ( !m_cameraControl )
			return;
		auto pos = glm::vec2 ( ( float ) x , ( float ) y );
		auto deltaPos = pos - m_prevMousePos;

		const float cameraRotSpeed = 0.8f;
		m_cameraYaw -= deltaPos.x * cameraRotSpeed;
		m_cameraPitch -= deltaPos.y * cameraRotSpeed;

		if ( m_cameraYaw < 0.0f )   m_cameraYaw += 360.0f;
		if ( m_cameraYaw > 360.0f ) m_cameraYaw -= 360.0f;

		if ( m_cameraPitch > 89.0f )  m_cameraPitch = 89.0f;
		if ( m_cameraPitch < -89.0f ) m_cameraPitch = -89.0f;


		m_prevMousePos = pos;
	}

	void CameraCalcul ( ) {
		m_cameraFront =
			glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( m_cameraYaw ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) )
			* glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( m_cameraPitch ) , glm::vec3 ( 1.0f , 0.0f , 0.0f ) )
			* glm::vec4 ( 0.0f , 0.0f , -1.0f , 0.0f );   //방향벡터에는 4번째 항에 0을 넣음


		projection = glm::perspective ( glm::radians ( SightAngle ) , ( float ) Height / ( float ) Widht , SightNear , SightFar );   //원근투영

		//카메라 위치 함수
		view = glm::lookAt ( m_cameraPos , m_cameraPos + m_cameraFront , m_cameraUp );
	}


	glm::mat4& GetProjection ( ) {
		return projection;
	}

	glm::vec3& GetCameraFront ( ) {
		return m_cameraFront;
	}
	
	glm::mat4& GetView ( ) {
		return view;
	}

	glm::vec3& GetPos ( ) {
		return m_cameraPos;
	}
};