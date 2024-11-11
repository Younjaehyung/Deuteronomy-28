#pragma once
#include "Component.h"

class ColiderComponent : public Component{
private:
	uint32_t mID;
	


public:
	ColiderComponent ( );
	~ColiderComponent ( );

	virtual void Update ( );
	virtual void Initialize ( );
	virtual void FixedUpdate ( );
	virtual void Render ( );

	uint32_t GetID ( ) {
		return mID;
	}


};