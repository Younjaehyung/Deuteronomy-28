#pragma once

#include "Camera.h"

class CameraManager {

private:
	CameraManager ( ) {}
	std::vector<Camera*> Cameras;

	Camera* using_Camera= nullptr;
	Camera* using_Camera2 = nullptr;


	bool m_cameraControl = true;
	bool m_camera2Control = false;

public:
	static CameraManager& getInstance ( ) {
		static CameraManager instance;
		return instance;
	}

	void ResetCamera ( ) {
		Cameras.clear ( );
		m_cameraControl = true;
		m_camera2Control = false;
	}

	bool& ClickCamera ( ) {

		//return using_Camera->cameraControl();
		return m_cameraControl;
	}

	void Update ( ) {
		/*for ( auto _Camera : Cameras ) {
			_Camera->Update ( );
		}*/
		
		
		using_Camera->Update ( );
		using_Camera2->Update ( );
	}

	void AddCamera (Camera* addcamera ) {
		for ( auto& _camera : Cameras ) {
			if ( addcamera == _camera ) {
				std::cout << "This Camera already exists" << std::endl;
				return;
			}
		}
		
		Cameras.push_back ( addcamera );
	}

	////////////////cmaera1
	glm::vec3& GetCameraPos ( ) {
		return using_Camera->GetPos ( );
	}

	glm::mat4& GetView ( ) {
		return using_Camera->GetView ( );
	}

	glm::vec3& GetCameraFront ( ) {
		return using_Camera->GetCameraFront ( );
	}
	

	void Input ( double x , double y ) {
		if ( !m_cameraControl ) {
			return;
		}
		using_Camera->MouseMove ( x,y );
		
	}

	glm::mat4 Camera_transform ( ) {
		return using_Camera->GetTransform();
	}



	void SetCamera ( Camera* setCamera ) {
		if ( using_Camera != nullptr ) {
			using_Camera->cameraControl ()= false;
		}
		using_Camera = setCamera;
		using_Camera->cameraControl ( )=true;
	}
	glm::vec2& GetCusor ( ) {
		return using_Camera->GetCusor();
	}


	////////////////cmaera2

	glm::vec3& GetCamera2Pos ( ) {
		return using_Camera2->GetPos ( );
	}

	glm::mat4& GetView2 ( ) {
		return using_Camera2->GetView ( );
	}

	glm::vec3& GetCamera2Front ( ) {
		return using_Camera2->GetCameraFront ( );
	}


	glm::mat4 Camera2_transform ( ) {
		return using_Camera2->GetTransform ( );
	}



	void SetCamera2 ( Camera* setCamera ) {
		if ( using_Camera2 != nullptr ) {
			using_Camera2->cameraControl ( ) = false;
		}
		using_Camera2 = setCamera;
		using_Camera2->cameraControl ( ) = true;

	}

	
};