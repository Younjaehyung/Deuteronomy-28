#pragma once
#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <random>

enum class moving {
	stop ,
	walk ,
	run ,
	sit ,
	sit_walk ,
};

class Camera
{
private:
	bool static_camera = 0;	//카메라가 정적인지 아닌지

	bool m_cameraControl = false;	//카메라가 작동중인지 아닌지
	enum moving Ismoving = moving::stop;
	float moving_Time = 0.0f;
	//카메라
	float m_cameraPitch{ 0.0f };
	
	float m_cameraYaw{ 0.0f };
	float m_camerRoll{ 0.0f };

	float m_TcameraPitch{ 0.0f };

	float m_TcameraYaw{ 0.0f };
	float m_TcamerRoll{ 0.0f };

	glm::vec3 m_cameraPos{ glm::vec3 ( 0.0f, 0.0f, 0.0f ) };	//카메라의 위치
	glm::vec3 m_cameraFront{ glm::vec3 ( 0.0f, 0.0f, -1.0f ) };	//카메라가 보고 있는 방향
	glm::vec3 m_cameraUp{ glm::vec3 ( 0.0f, 1.0f, 0.0f ) };		//카메라 up벡터


	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4 ( 1.0f );

	float SightNear = 0.1f;
	float SightFar = 150.0f;
	float SightAngle = 50.0f;

	float Widht = 1080.f;
	float Height = 1920.f;

	
	glm::vec2 m_prevMousePos{ glm::vec2 ( 0.0f ) };
	glm::vec2  deltaPos;
	float elpasedTime{};
public:
	
	Camera ( ) {

	}

	glm::vec2& GetCusor ( ) {
		return m_prevMousePos;
	}

	void Debugging ( ) {

	}

	
	
	void Camera_set (glm::vec3 _pos) {
		m_cameraPos = _pos;
	}

	enum moving& Camera_Ismoving ( enum moving ismoving ) {
		Ismoving = ismoving;
		return Ismoving;
	}

	void Update ( );
	void MouseMove ( double x , double y );
	


	glm::mat4 GetTransform ( ) {
		return projection * view;
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

	glm::vec3 GetFront ( ) {
		return m_cameraFront;
	}
	
	glm::vec3& GetPos ( ) {
		return m_cameraPos;
	}

	glm::mat4 GetDir ( ) {
		return glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( m_cameraYaw ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) )
			* glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( m_cameraPitch ) , glm::vec3 ( 1.0f , 0.0f , 0.0f ) );
	}

	glm::mat4 GetYaw ( ) {
		return glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( m_cameraYaw ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
			
	}

	void SetCamera ( glm::vec3 _pos , glm::vec3 _dir , glm::vec3 _up= glm::vec3 ( 0.0f , 0.0f , 1.0f ),float Near = 0.1f , float Far = 150.f , float Angle = 50.0f );
	
	bool& cameraControl ( ) {
		return m_cameraControl;
	}

private:
		static inline float WrapDeg ( float a ) {
			a = std::fmod ( a , 360.f );
			if ( a < 0.f ) a += 360.f;
			return a;
		}
		static inline float ShortestAngleDeltaDeg ( float from , float to ) {
			float d = std::fmod ( to - from + 540.f , 360.f ) - 180.f; // [-180,180)
			return d;
		}
};

