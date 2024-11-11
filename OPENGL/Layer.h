#pragma once
#include "Gameobject.h"
#include "Component.h"
#include <vector>
#include <time.h>

class Layer {
private:
	std::vector <Gameobject*> Gameobjects;
public:

	void Update ( )
	{
		for (auto& _Gameobject : Gameobjects ) {
			_Gameobject->Update (Time::DeltaTime() );
		}
	}

	void Initialize ( )
	{
		for ( auto& _Gameobject : Gameobjects ) {
			
		}
	}

	void FixedUpdate ( )
	{
		for ( auto& _Gameobject : Gameobjects ) {
			_Gameobject->FixedUpdate ( );
		}
	}

	void AddGameobjects ( Gameobject* _Gameobject ) {
		Gameobjects.push_back ( _Gameobject );
	}

	void Render ( )
	{
		for ( auto& _Gameobject : Gameobjects ) {
			_Gameobject->Render ( );
		}

	}

};