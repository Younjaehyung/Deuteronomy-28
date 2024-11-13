#pragma once

#include "Camera.h"

class CameraManager {

private:
	CameraManager ( ) {}
	std::vector<Camera*> Cameras;

	Camera* using_Camera= nullptr;

public:
	static CameraManager& getInstance ( ) {
		static CameraManager instance;
		return instance;
	}

	void Update ( ) {
		/*for ( auto _Camera : Cameras ) {
			_Camera->Update ( );
		}*/
		
		using_Camera->Update ( );
	}

	glm::vec3& GetCameraPos ( ) {
		return using_Camera->GetPos ( );
	}


	void Input ( double x , double y ) {
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

};