#include "Gameobject.h"

//Update
void Gameobject::Update ( float deltaTime ) {
	for ( auto& _components : m_vecComponent ) {
		_components->Update ( deltaTime );
	}
}

void Gameobject::FixedUpdate ( ) {
	for ( auto& _components : m_vecComponent ) {
		_components->FixedUpdate ( );
	}
}


void Gameobject::Render ( ) {
	
	auto CameraFront = CameraManager::getInstance ( ).GetCameraFront();
	auto Projection = CameraManager::getInstance ( ).GetProjection();
	auto View=	CameraManager::getInstance ( ).GetView() ;

	for ( auto& _components : m_vecComponent ) {
		_components->Render ( 
			CameraFront ,
			Projection ,
			View );
	}
}
