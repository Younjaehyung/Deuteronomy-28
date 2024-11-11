#pragma once
#include "Component.h"
#include "input.h"

class InputComponent :public Component {
public:
	InputComponent ( Gameobject* pOwner ):Component( pOwner){}
	virtual ~InputComponent ( ) {}

	virtual void Update ( float deltaTime ) {}
private:


};

class PlayerInputComponent:public InputComponent {
public:
	void Update (float deltaTime ) {
	
		
		Move (  );
		Dir (  );
	}
	PlayerInputComponent ( Gameobject* pOwner ) :InputComponent ( pOwner ) {}
	virtual ~PlayerInputComponent ( ) {}

private:
	float walkLevel = 1.0f;

	void Move ( );

	void Dir ( );
};
