#include "InputComponent.h"
#include "Gameobject.h"
#include "CameraManager.h"

void PlayerInputComponent:: Move ( ) {
	Gameobject* obj = GenOwner ( );

	glm::vec3 OBJPOS = obj->GetPos ( );

	if ( input::GetKey ( eKeyCode::W ) ) {
		OBJPOS.z -= walkLevel;
	}
	if ( input::GetKey ( eKeyCode::A ) ) {
		OBJPOS.x -= walkLevel;
	}
	if ( input::GetKey ( eKeyCode::S ) ) {
		OBJPOS.z += walkLevel;
	}
	if ( input::GetKey ( eKeyCode::D ) ) {
		OBJPOS.x += walkLevel;
	}

	obj->SetPos ( OBJPOS );

	CameraManager::getInstance ( ).CameraPos ( obj->GetPos ( ) );
}

void PlayerInputComponent::Dir ( ) {
	Gameobject* obj = GenOwner ( );
	CameraManager::getInstance ( ).CameraPos ( obj->GetDir ( ) );
}
